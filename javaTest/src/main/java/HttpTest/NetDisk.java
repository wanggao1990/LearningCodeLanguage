package HttpTest;

import HttpTest.HttpClient;
import com.sun.istack.internal.NotNull;
import org.elasticsearch.common.Nullable;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class NetDisk {

    private final static String service = "http://192.168.3.55:8500";

    private String Post(String url, Map<String, String> params) throws Exception {

        URL uri = new URL(url);
        HttpURLConnection conn = (HttpURLConnection) uri.openConnection();
        conn.setReadTimeout(10 * 1000);// 缓存的最长时间
        conn.setDoInput(true);// 允许输入
        conn.setDoOutput(true);// 允许输出
        conn.setUseCaches(false);// 不允许使用缓存
        conn.setRequestMethod("POST");
        conn.setRequestProperty("connection", "keep-alive");
        conn.setRequestProperty("Charsert", "UTF-8");
        conn.setRequestProperty("User-Agent", "Mozilla/4.0 (compatible; MSIE 5.0; Windows NT; DigExt)");
        conn.connect();

        // 首先组拼文本类型的参数
        StringBuilder sb = new StringBuilder();
        for (Map.Entry<String, String> entry : params.entrySet()) {
            if (sb.length() != 0) {
                sb.append("&");
            }
            sb.append(entry.getKey() + "=" + entry.getValue());
        }
        OutputStream outStream = conn.getOutputStream();
        outStream.write(sb.toString().getBytes());
        outStream.close();

        // 得到响应码
        int res = conn.getResponseCode();
        InputStream inStream = conn.getInputStream();
        StringBuilder sb2 = new StringBuilder();
        if (res == 200) {
            int ch;
            while ((ch = inStream.read()) != -1) {
                sb2.append((char) ch);
            }
        }
        inStream.close();

        conn.disconnect();
        return sb2.toString();
    }


    private String Post(String url, Map<String, String> params, Map<String, File> files) throws Exception {
        try {
            String BOUNDARY = java.util.UUID.randomUUID().toString();
            String PREFIX = "--", LINEND = "\r\n";
            String MULTIPART_FROM_DATA = "multipart/form-data", CHARSET ="UTF-8";
            URL uri = new URL(url);
            HttpURLConnection conn = (HttpURLConnection) uri.openConnection();
            conn.setReadTimeout(10 * 1000);// 缓存的最长时间
            conn.setDoInput(true);// 允许输入
            conn.setDoOutput(true);// 允许输出
            conn.setUseCaches(false);// 不允许使用缓存
            conn.setRequestMethod("POST");
            conn.setRequestProperty("connection", "keep-alive");
            conn.setRequestProperty("Charsert", "UTF-8");
            conn.setRequestProperty("User-Agent", "Mozilla/4.0 (compatible; MSIE 5.0; Windows NT; DigExt)");
            conn.setRequestProperty("Content-Type", MULTIPART_FROM_DATA + ";boundary="/* + PREFIX*/ + BOUNDARY);

            // 首先组拼文本类型的参数
            StringBuilder sb = new StringBuilder();
            for (Map.Entry<String, String> entry : params.entrySet()) {
                //  sb.append(LINEND);
                sb.append(PREFIX + BOUNDARY + LINEND);
                sb.append("Content-Disposition: form-data; name=\"" + entry.getKey() + "\"" + LINEND);
                sb.append("Content-Type: text/plain; charset=" + CHARSET + LINEND);
                sb.append("Content-Transfer-Encoding: 8bit" + LINEND);
                sb.append(LINEND);
                sb.append(entry.getValue());
                sb.append(LINEND);
            }
            DataOutputStream outStream = new DataOutputStream(conn.getOutputStream());
            outStream.write(sb.toString().getBytes());

            // 发送文件数据
            if (files != null) {
                for (Map.Entry<String, File> file : files.entrySet()) {

                    String filename = file.getValue().getName();
                    String imageType = "image/" + filename.substring(filename.indexOf('.') + 1);

                    StringBuilder sb1 = new StringBuilder();
                    sb1.append(PREFIX + BOUNDARY + LINEND);
                    sb1.append("Content-Disposition: form-data; name=\"" + file.getKey() + "\"; filename=\""
                            + filename + "\"" + LINEND);
                    sb1.append("Content-Type: application/octet-stream; charset=" + CHARSET + LINEND);
                    //    sb1.append("Content-Type: " + imageType + LINEND);
                    sb1.append(LINEND);
                    outStream.write(sb1.toString().getBytes());
                    InputStream is = new FileInputStream(file.getValue());
                    byte[] buffer = new byte[1024];
                    int len = 0;
                    while ((len = is.read(buffer)) != -1) {
                        outStream.write(buffer, 0, len);
                    }
                    is.close();
                    outStream.write(LINEND.getBytes());
                }
            }
            // 请求结束标志
            byte[] end_data = (PREFIX + BOUNDARY + PREFIX + LINEND).getBytes();
            outStream.write(end_data);
            outStream.flush();


            // 得到响应码
            int res = conn.getResponseCode();
            InputStream in = conn.getInputStream();

            StringBuilder sb2 = new StringBuilder();
            if (res == 200) {
                int ch;
                while ((ch = in.read()) != -1) {
                    sb2.append((char) ch);
                }
            }
            outStream.close();
            conn.disconnect();
            return sb2.toString();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "";
    }


    public void Login() {
        try {

            String httpUrl = service + "/api/user/login";

            Map<String, String> params = new HashMap<>();
            params.put("email", "wangaf@magicsky.com");
            params.put("password", "123456");

            String res = Post(httpUrl, params, /*new HashMap<>()*/ null);

            System.out.println(res);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void Upload() {
        try {
            String httpUrl = service + "/api/matter/upload";

            Map<String, String> params = new HashMap<>();
            params.put("userUuid", "736a5551-cc60-47f9-4933-489e475958a5");
            params.put("puuid", "root");

            Map<String, File> files = new HashMap<>();
            files.put("file", new File("C:\\Users\\wanggao\\Desktop\\1.png"));

            String res = Post(httpUrl, params, files);

            System.out.println(res);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {

        String uuid = UUID.randomUUID().toString();
        System.out.println(uuid);

        NetDisk instant = new NetDisk();
       // instant.Login();
        instant.Upload();
    }


}
