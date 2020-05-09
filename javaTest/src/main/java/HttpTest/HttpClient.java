package HttpTest;

import java.io.*;
import java.net.URL;
import java.net.URLConnection;
import java.nio.charset.Charset;
import java.util.List;
import java.util.Map;



public class HttpClient {
    public static String sendGet(String url, String param) {
        String result = "";
        BufferedReader in = null;
        try {
            String urlNameString = url + "?" + param;
            URL realUrl = new URL(urlNameString);
            // 打开和URL之间的连接
            URLConnection connection = realUrl.openConnection();
            // 设置通用的请求属性
            connection.setRequestProperty("accept", "*/*");
            connection.setRequestProperty("connection", "Keep-Alive");
            connection.setRequestProperty("user-agent",
                    "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1;SV1)");
            // 建立实际的连接
            connection.connect();
            // 获取所有响应头字段
            Map<String, List<String>> map = connection.getHeaderFields();
            // 遍历所有的响应头字段
            for (String key : map.keySet()) {
                System.out.println(key + "--->" + map.get(key));
            }
            // 定义 BufferedReader输入流来读取URL的响应
            in = new BufferedReader(new InputStreamReader(
                    connection.getInputStream()));
            String line;
            while ((line = in.readLine()) != null) {
                result += line;
            }
        } catch (Exception e) {
            System.out.println("发送GET请求出现异常！" + e);
            e.printStackTrace();
        } finally { // 使用finally块来关闭输入流
            try {
                if (in != null) {
                    in.close();
                }
            } catch (Exception e2) {
                e2.printStackTrace();
            }
        }
        return result;
    }

    /**
     * 向指定 URL 发送POST方法的请求
     *
     * @param url   发送请求的 URL
     * @param param 请求参数，请求参数应该是 name1=value1&name2=value2 的形式。
     * @return 所代表远程资源的响应结果
     */
    public static String sendPost(String url, String param) {
        PrintWriter out = null;
        BufferedReader in = null;
        String result = "";
        try {
            URL realUrl = new URL(url);
            // 打开和URL之间的连接
            URLConnection conn = realUrl.openConnection();
            // 设置通用的请求属性
            conn.setRequestProperty("accept", "*/*");
            conn.setRequestProperty("connection", "Keep-Alive");
            conn.setRequestProperty("user-agent",
                    "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1;SV1)");

            // 发送POST请求必须设置如下两行
            conn.setDoOutput(true);
            conn.setDoInput(true);
            // 获取URLConnection对象对应的输出流
            out = new PrintWriter(conn.getOutputStream());
            // 发送请求参数
            out.print(param);
            // flush输出流的缓冲
            out.flush();

            // 定义BufferedReader输入流来读取URL的响应
            in = new BufferedReader(
                    new InputStreamReader(conn.getInputStream()));
            String line;
            while ((line = in.readLine()) != null) {
                result += line;
            }
        } catch (Exception e) {
            System.out.println("发送 POST 请求出现异常！" + e);
            e.printStackTrace();
        } finally { //使用finally块来关闭输出流、输入流
            try {
                if (out != null) {
                    out.close();
                }
                if (in != null) {
                    in.close();
                }
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
        return result;
    }


    /**
     *
     * @param
     */
    public static void testCLient()
    {
        org.apache.commons.httpclient.HttpClient client =
                new org.apache.commons.httpclient.HttpClient();

        try {
            org.apache.commons.httpclient.methods.PostMethod postMethod = null;
            postMethod = new org.apache.commons.httpclient.methods.PostMethod(
                    "http://192.168.3.100:8080/api/ai_server/stop/mask_detector"
            );


            org.apache.commons.httpclient.methods.StringRequestEntity entity =
                    new org.apache.commons.httpclient.methods.StringRequestEntity("{\n" +
                            "\"rtmpUrl\":\"rtmp://222.190.143.158:9092/live/XUNI0000000001\",\n" +
                            "\"username\":\"magicsky\"\n" +
                            "}", "application/json", "UTF-8");

            postMethod.setRequestEntity(entity);


            int statusCode = client.executeMethod(postMethod);
            if(statusCode == 200) {
                String resp = postMethod.getResponseBodyAsString();
                System.out.println(resp);
            }else {

            }

        } catch (IOException e) {
            System.out.println(e.toString());
        }
        System.out.println("123");
    }



    public static void main(String[] args) {

        testCLient();


//        //发送 GET 请求
//        String s=HttpClient.sendGet("http://localhost:6144/Home/RequestString", "key=123&v=456");
//        System.out.println(s);

        //发送 POST 请求
        String param = new String(
                "uavModel=无人机型号&uavName=无人机1号&uavSn=201805171314&uavSw=version-0.1&appSwflag=软件标志".getBytes()
        );

        String sr = HttpClient.sendPost("http://192.168.19.130:8032/uavlog", param);
        System.out.println(sr);
    }


}
