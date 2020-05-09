package Utils;

import java.math.BigDecimal;

/**
 * @Auther: waf
 * @Date: 2018/11/22 17:40
 * @Description: 地图距离计算
 */
public class DistanceCalculateUtil {
    private final static double EARTH_RADIUS = 6378.137;//地球半径

    private static double rad(double d) {
        return d * Math.PI / 180.0;
    }

    /**
     * 计算两点间距离
     *
     * @return double 距离 单位公里,精确到米
     */
    public static double GetDistance(double lat1, double lng1, double lat2, double lng2) {
        double radLat1 = rad(lat1);
        double radLat2 = rad(lat2);
        double a = radLat1 - radLat2;
        double b = rad(lng1) - rad(lng2);
        double s = 2 * Math.asin(Math.sqrt(Math.pow(Math.sin(a / 2), 2) +
                Math.cos(radLat1) * Math.cos(radLat2) * Math.pow(Math.sin(b / 2), 2)));
        s = s * EARTH_RADIUS;
        s = new BigDecimal(s).setScale(3, BigDecimal.ROUND_HALF_UP).doubleValue();
        return s;
    }

    public static void main(String[] args) {
        //距离计算 UAV与侦听机经纬度为0时距离无效
//        Double uavLng = 118.861641;
//        Double uavLat = 32.157211;
//        Double listenerLng = 118.863235;
//        Double listenerLat = 32.157242;

        Double uavLng = 118.8630903;
        Double uavLat = 32.15737933;
        Double listenerLng = 118.8631112;
        Double listenerLat = 32.15737817;

        double distance = 1000 * DistanceCalculateUtil.GetDistance(uavLat, uavLng, listenerLat, listenerLng);
        System.out.println(distance);



        {
            Double lng = 118 + 51./60;
            Double lat = 32 + 9./60;

            {
                Double lng1 = lng + 47.2758/3600;
                Double lat1 = lat + 26.5661/3600;

                Double lng2 = lng + 47.5344/3600;
                Double lat2 = lat + 26.7012/3600;

                double d = 1000 * DistanceCalculateUtil.GetDistance(lat1, lng1, lat2, lng2);
                System.out.println(d);
            }


            {
                Double lng1 = lng + 47.4498/3600;
                Double lat1 = lat + 26.573/3600;

                Double lng2 = lng + 47.5344/3600;
                Double lat2 = lat + 26.7012/3600;

                double d = 1000 * DistanceCalculateUtil.GetDistance(lat1, lng1, lat2, lng2);
                System.out.println(d);
            }


        }

    }
}
