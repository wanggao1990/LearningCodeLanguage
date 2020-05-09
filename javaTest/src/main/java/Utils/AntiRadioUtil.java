package Utils;

import java.math.BigDecimal;

public class AntiRadioUtil {


    private final static double EARTH_RADIUS = 6378.137;//地球半径

    /**
     * 计算两点间距离
     *
     * @return double 距离 单位公里,精确到米
     */
    private static double computerDistance(double lat1, double lon1, double lat2, double lon2) {
        double radLat1 = Math.toRadians(lat1), radLat2 = Math.toRadians(lat2);
        double a = radLat1 - radLat2, b = Math.toRadians(lon1) - Math.toRadians(lon2);
        double s = 2 * Math.asin(Math.sqrt(Math.pow(Math.sin(a / 2), 2) +
                Math.cos(radLat1) * Math.cos(radLat2) * Math.pow(Math.sin(b / 2), 2)));
        s = s * EARTH_RADIUS;
        s = new BigDecimal(s).setScale(3, BigDecimal.ROUND_HALF_UP).doubleValue();
        return s;
    }

    /**
     *  计算目标[lon2,lat2] 相对设备 [lon1,lat1]的方位角
     *
     * @param lat1,lon1 设备的经纬度
     * @param lat2,lon2 目标经纬度
     * @return double 方位角 [-180,180], 正北0度, 逆时针[0, -180], 顺时针[0-180]
     */
    private static double computeAzimuth(double lat1, double lon1, double lat2, double lon2){
        double result = 0.;
        int ilat1 = (int)(0.50 + lat1 * 360000), ilon1 = (int)(0.50 + lon1 * 360000);
        int ilat2 = (int)(0.50 + lat2 * 360000), ilon2 = (int)(0.50 + lon2 * 360000);

        lat1 = Math.toRadians(lat1);  lon1 = Math.toRadians(lon1);
        lat2 = Math.toRadians(lat2);  lon2 = Math.toRadians(lon2);

        if ((ilat1 == ilat2) && (ilon1 == ilon2)) {
            return result;
        } else if (ilon1 == ilon2) {
            if (ilat1 > ilat2)
                result = 180.0;
        } else {
            double c = Math.acos(Math.sin(lat2) * Math.sin(lat1) + Math.cos(lat2)
                    * Math.cos(lat1) * Math.cos((lon2 - lon1)));

            double A = Math.asin(Math.cos(lat2) * Math.sin((lon2 - lon1)) / Math.sin(c));

            result = Math.toDegrees(A);

            if ((ilat2 > ilat1) && (ilon2 > ilon1)) {
            } else if ((ilat2 < ilat1) && (ilon2 < ilon1)) {
                result = 180.0 - result;
            } else if ((ilat2 < ilat1) && (ilon2 > ilon1)) {
                result = 180.0 - result;
            } else if ((ilat2 > ilat1) && (ilon2 < ilon1)) {
                result += 360.0;
            }
        }

        // => [0-360]
        if(result<0)         result +=360.0;
        else if(result>360)  result -=360.0;

        // 正北 逆时针[0, -180] 顺时针[0-180]
        if(result > 180)     result -= 360;

        return result;
    }

    /**
     *  计算目标[lon2,lat2] 相对设备 [lon1,lat1]的方位角, 俯仰角
     *
     * @param lat1,lon1 设备的经纬度
     * @param lat2,lon2 目标经纬度
     * @param altitude  目标高度
     * @return double 方位角，俯仰角
     */
    public static double[] calcAzimuthPith(double lat1, double lon1, double lat2, double lon2, double altitude)
    {
        double[] res = new double[2];
        double dis = computerDistance(lat1, lon1, lat2, lon2);
        res[0] = computeAzimuth(lat1, lon1, lat2, lon2);
        res[1] = Math.toDegrees(Math.atan(altitude/dis));
        return  res;
    }

    public static void main(String[] args) {
       // System.out.println(computerDistance(32.0,128,32.1,129));

        double[] res = calcAzimuthPith(32.0,128,32.1,129, 120);
        System.out.printf("%f, %f",res[0],res[1]);
    }
}
