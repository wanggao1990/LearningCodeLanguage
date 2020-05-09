package ElasticSearchUtil;

import java.io.BufferedReader;
import java.io.FileReader;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import com.google.gson.JsonObject;
import com.sun.xml.internal.ws.api.ha.StickyFeature;
import org.elasticsearch.action.admin.indices.create.CreateIndexResponse;
import org.elasticsearch.action.index.IndexRequestBuilder;
import org.elasticsearch.action.search.SearchRequestBuilder;
import org.elasticsearch.action.search.SearchResponse;
import org.elasticsearch.client.Client;
import org.elasticsearch.client.IndicesAdminClient;
import org.elasticsearch.common.settings.Settings;
import org.elasticsearch.client.transport.TransportClient;
import org.elasticsearch.common.transport.InetSocketTransportAddress;
import org.elasticsearch.common.unit.TimeValue;
import org.elasticsearch.common.xcontent.XContentBuilder;
import org.elasticsearch.common.xcontent.XContentFactory;
import org.elasticsearch.index.query.QueryBuilder;
import org.elasticsearch.index.query.QueryBuilders;
import org.elasticsearch.search.SearchHit;
import org.elasticsearch.search.SearchHits;
import org.elasticsearch.transport.client.PreBuiltTransportClient;


public class ESClient {
    private static Client client;

    public ESClient(String host, int port) {
        try {
            if (client == null){
                init(host, port);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 初始化客户端
     * */
    private void init(String host, int port) throws Exception {
        //byte[] bs = new byte[] { (byte) 192, (byte) 168, (byte)52, (byte)130 };

//        client = TransportClient.builder().build().addTransportAddress(new InetSocketTransportAddress(
//                InetAddress.getByAddress(bs), port));

        Settings settings = Settings.builder()
                //.put("cluster.name", "my-application").build();
                .put("cluster.name", "MAGICSKYES").build();
        client = new PreBuiltTransportClient(settings).addTransportAddress(new InetSocketTransportAddress(InetAddress.getByName(host), port));

        //SearchResponse searchResponse = client.prepareSearch().execute().actionGet();
        //System.out.println(searchResponse.status());

    }

    public Client getClient() {
        return client;
    }


    /**
     * 创建空索引  默认setting 无mapping
     * @param index
     * @return
     */
    public boolean createSimpleIndex( String index){
        IndicesAdminClient indicesAdminClient = client.admin().indices();
        CreateIndexResponse response = indicesAdminClient.prepareCreate(index).get();
        return response.isAcknowledged();
    }

    /**
     * 创建索引 指定setting,创建mapper
     * @param index
     * @return
     */
    public boolean createIndex(String index){
        // settings
        Settings settings = Settings.builder()
                .put("index.number_of_shards", 1)
                .put("index.number_of_replicas", 0)
                //.put("cluster.name", "poc")
                //.put("node.name", "node1")
                //.put("client.transport.ignore_cluster_name", true)
                //.put("node.client", true)
                //.put("client.transport.sniff", true)
                .build();
        // mapping
        XContentBuilder mappingBuilder;
        try {
            mappingBuilder = XContentFactory.jsonBuilder()
                    .startObject()
                    .startObject(index)
                    .startObject("properties")
                    .startObject("ID").field("type", "string").field("store", "yes").endObject()
                    .startObject("IP").field("type", "string").field("store", "yes").endObject()
                    .startObject("VALUE_DAY").field("type", "string").field("store", "yes").endObject()
                    .startObject("GROUPNAME").field("type", "string").field("store", "yes").endObject()
                    .startObject("TYPE_MACHINE").field("type", "string").field("store", "yes").endObject()
                    .startObject("DATE").field("type", "string").field("store", "yes").endObject()
                    .startObject("TYPE").field("type", "string").field("store", "yes").endObject()
                    .endObject()
                    .endObject()
                    .endObject();
        } catch (Exception e) {
            System.out.println("--------- createIndex 创建 mapping 失败：" + e);
            return false;
        }
        IndicesAdminClient indicesAdminClient = client.admin().indices();
        CreateIndexResponse response = indicesAdminClient.prepareCreate(index)
                .setSettings(settings)
                .addMapping(index, mappingBuilder)
                .get();
        return response.isAcknowledged();
    }

    public static List<String> dataCreater(String path) throws Exception {

        FileReader fr = new FileReader(path);
        BufferedReader br = new BufferedReader(fr);
        String line=null;
        List<String> dataList = new ArrayList<String>();

        while((line = br.readLine()) != null){
            String[] data = line.split("\t");
            JsonObject jsonObject = new JsonObject();
            jsonObject.addProperty("ID", data[0]);
            jsonObject.addProperty("IP", data[1]);
            jsonObject.addProperty("VALUE_DAY", data[2]);
            jsonObject.addProperty("GROUPNAME", data[3]);
            jsonObject.addProperty("TYPE_MACHINE", data[4]);
            jsonObject.addProperty("DATE", data[5]);
            jsonObject.addProperty("TYPE", data[6]);
            dataList.add(jsonObject.toString());
        }

        br.close();
        fr.close();

        return dataList;
    }


    /**
     * 数据写入索引
     * @param index
     * @return
     * @throws Exception
     */
//    public void write(String index, String tablename, String filePath) throws Exception {
//
//        //创建索引库 需要注意的是.setRefresh(true)这里一定要设置,否则第一次建立索引查找不到数据
//        IndexRequestBuilder requestBuilder = client.prepareIndex(index, tablename).setRefresh(true);
//        List<String> dataList = this.dataCreater(filePath);
//        for (String data : dataList) {
//            System.out.println(data);
//            requestBuilder.setSource(data).execute().actionGet();
//        }
//    }

    /**
     * 查询全部内容，实现分页查询
     * */
    public List<String> searchAll( String index, String table) {

        SearchResponse response = client.prepareSearch().setIndices(index).setTypes(table).get();
        int n = (int) response.getHits().totalHits();
        int size = 100;
        List<String> retList = new ArrayList<String>();

        for(int i = 0;i < n;){
            response = client.prepareSearch().setIndices(index).setTypes(table).setScroll(TimeValue.timeValueMinutes(2)).setFrom(i).setSize(size).get();
            i += size;
            SearchHits searchHits = response.getHits();
            for (SearchHit hit : searchHits) {
                retList.add(hit.getSourceAsString());
            }
        }
        return retList;
    }

    /**
     * 使用过滤器查询，实现分页查询
     * */
    public List<String> queryByFilter(String index, String table) {

        // 查询groupname为"压力测试"的数据
        QueryBuilder queryBuilder = QueryBuilders.matchQuery("GROUPNAME", "压力测试");

        SearchResponse response = client.prepareSearch().setIndices(index).setTypes(table).setQuery(queryBuilder).get();
        int n = (int) response.getHits().totalHits();
        System.out.println(n);
        int size = 100;
        List<String> retList = new ArrayList<String>();

        response = client.prepareSearch().setIndices(index).setTypes(table).setScroll(TimeValue.timeValueMinutes(5)).setSize(n).setQuery(queryBuilder).get();
        SearchHits searchHits = response.getHits();
        for (SearchHit hit : searchHits) {
            retList.add(hit.getSourceAsString());
        }
        return retList;
    }


    public static void main(String[] args) {

        String host = "192.168.3.171";
        int port = 9300;

        ESClient client = null;

        try {
            //  创建客户端
            client = new ESClient(host, port);

//        // 创建索引
//        String newIndex = new Date().toString();
//        client.createIndex(newIndex);
//
//        //元数据写入索引文件
//        try {
//            client.write("poc","metadata", "data/poc");
//        } catch (Exception e) {
//            e.printStackTrace();
//        }

//            // 查询
//            List<String> ret = client.queryByFilter("poc", "metadata");
//            System.out.println(ret.size());
//            System.out.println(ret);



            SearchRequestBuilder searchRequestBuilder = client.getClient().prepareSearch("aeroscope-log-2018.11.22")
                    .setTypes("aeroscope-log")
                    .setQuery(QueryBuilders.termQuery("flyDirection", "-122.339996"));
            System.out.println(searchRequestBuilder);
            SearchHit[] hits = searchRequestBuilder.get().getHits().getHits();
            for(SearchHit hit : hits){
                System.out.println(hit.getSourceAsString());
            }

        }catch (Exception e){
            e.printStackTrace();

            client.getClient().close();
        }


    }
}

