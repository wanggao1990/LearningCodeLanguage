package ElasticSearchUtil;


import com.google.gson.GsonBuilder;
import com.google.gson.JsonObject;
import io.searchbox.client.JestClient;
import io.searchbox.client.JestClientFactory;
import io.searchbox.client.config.HttpClientConfig;

import io.searchbox.core.Search;
import io.searchbox.core.SearchResult;

import org.elasticsearch.index.query.BoolQueryBuilder;
import org.elasticsearch.index.query.QueryBuilders;
import org.elasticsearch.search.builder.SearchSourceBuilder;
import org.elasticsearch.search.sort.SortOrder;

import java.io.IOException;

public class JestTest {


    public static void main(String[] args) {
        JestClient client = null;
        try {
            JestClientFactory factory = new JestClientFactory();
            factory.setHttpClientConfig(new HttpClientConfig
                    .Builder("http://192.168.3.171:9200")
                    .gson(new GsonBuilder().setDateFormat("yyyy-MM-dd'T'hh:mm:ss").create())
                    .connTimeout(1500)
                    .readTimeout(3000)
                    .multiThreaded(true)
                    .build()
            );

            client = factory.getObject();




//            BoolQueryBuilder boolQueryBuilder = QueryBuilders.boolQuery()
//                    .must(QueryBuilders.queryStringQuery("d1ebd620-2191-4444-ba3b-80e0f57941ef").defaultField("uuid"));


//            BoolQueryBuilder boolQueryBuilder = QueryBuilders.boolQuery()
//                    .must(QueryBuilders.matchQuery("uuid","d1ebd620-2191-4444-ba3b-80e0f57941ef").fuzzyTranspositions(false));

            BoolQueryBuilder boolQueryBuilder = QueryBuilders.boolQuery()
                    .must(QueryBuilders.commonTermsQuery("uuid","1e5598e3-b678-4283-82a3-f485a4709aa4"));   // 也是模糊匹配，   若要记录正确，需要给完整的uuid

            SearchSourceBuilder searchSourceBuilder = new SearchSourceBuilder()
                    .query(boolQueryBuilder)
                    .sort("logdate", SortOrder.DESC)
                    .size(10000);

            Search search = new Search.Builder(searchSourceBuilder.toString())
                    .addIndex("aeroscope-log-2019.04.23")
                    .addType("aeroscope-log")
                    .build();

            SearchResult searchResult = client.execute(search);

            if (searchResult != null && !searchResult.isSucceeded()) {
                throw new Exception("[服务端][ES search with Class]:" + searchResult.getErrorMessage());
            }

            JsonObject res = searchResult.getJsonObject();
            //System.out.println(res);

        } catch(Exception e){
            e.printStackTrace();

        }finally {
            try {
                client.close();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        }
    }
}
