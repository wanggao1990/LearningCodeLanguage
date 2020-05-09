package Utils;

public class CoordinateConvertUtil {

    /**
     * 世界标准地理坐标(WGS-84) 转换成 中国国测局地理坐标（GCJ-02）<火星坐标>
     *
     * @param dto 无人机实时数据
     */
/*
    public static void gps84_To_Gcj02(ScheduledDataPushDevInfoDTO dto) {

        //aircraft坐标
        String aircraftLongitude = dto.getAircraftLocationLongitude();
        String aircraftLatitude = dto.getAircraftLocationLatitude();

        double[] aircraftResult = CoordinateConvertUtil.gps84_To_Gcj02_Str(aircraftLongitude, aircraftLatitude);
        dto.setAircraftLocationLongitude(String.valueOf(aircraftResult[0]));
        dto.setAircraftLocationLatitude(String.valueOf(aircraftResult[1]));

        //home坐标
        String homeLongitude = dto.getHomeLocationLongitude();
        String homeLatitude = dto.getHomeLocationLatitude();
        double[] homeResult = CoordinateConvertUtil.gps84_To_Gcj02_Str(homeLongitude, homeLatitude);

        dto.setHomeLocationLongitude(String.valueOf(homeResult[0]));
        dto.setHomeLocationLatitude(String.valueOf(homeResult[1]));

        //path坐标
        List<double[]> flightPath = dto.getFlightPath();
        for (int i=0;i<flightPath.size();i++){

            double[] result = CoordinateConvertUtil.gps84_To_Gcj02_Double(flightPath.get(i)[0], flightPath.get(i)[1]);
            flightPath.set(i,result);
        }
    }
*/
    public static void main(String[] args) {


//        boolean zero = Double.valueOf(-1.000000) < 0;
//
//        boolean ret = Double.doubleToLongBits(0.000000) == Double.doubleToLongBits(0);
//        ret = Double.doubleToLongBits(0.02) > Double.doubleToLongBits(0.01);
//        ret = Double.doubleToLongBits(0.02) < Double.doubleToLongBits(0.01);


        double[] gps = gps84_To_Gcj02_Str("118.863", "32.1566");
        System.out.println(gps[0] + "  " + gps[1]);




    }

    public static double[] gps84_To_Gcj02_Str(String lng, String lat) {

        Double latitude = Double.parseDouble(lat);
        Double longitude = Double.parseDouble(lng);

        if (CoordinateConvertUtil.outOfChina(latitude, longitude)) {
            double[] point = {latitude, longitude};
            return point;
        }
        double[] delta = CoordinateConvertUtil.delta(latitude, longitude);
        double[] point = {longitude + delta[1], latitude + delta[0]};
        return point;
    }



    /**
     * 世界标准地理坐标(WGS-84)
     *
     * @return 中国国测局地理坐标（GCJ-02）<火星坐标>
     */
    public static double[] gps84_To_Gcj02_Double(double longitude, double latitude) {

        if (CoordinateConvertUtil.outOfChina(latitude, longitude)) {
            double[] point = {latitude, longitude};
            return point;
        }
        double[] delta = CoordinateConvertUtil.delta(latitude, longitude);
        double[] point = {longitude + delta[1], latitude + delta[0]};
        return point;
    }

    private static boolean outOfChina(double lat, double lng) {
        if ((lng < 72.004) || (lng > 137.8347)) {
            return true;
        }
        if ((lat < 0.8293) || (lat > 55.8271)) {
            return true;
        }
        return false;
    }

    private static double transformLat(double x, double y) {
        double ret =
                -100.0 + 2.0 * x + 3.0 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * Math.sqrt(Math.abs(x));
        ret += (20.0 * Math.sin(6.0 * x * Math.PI) + 20.0 * Math.sin(2.0 * x * Math.PI)) * 2.0 / 3.0;
        ret += (20.0 * Math.sin(y * Math.PI) + 40.0 * Math.sin(y / 3.0 * Math.PI)) * 2.0 / 3.0;
        ret += (160.0 * Math.sin(y / 12.0 * Math.PI) + 320 * Math.sin(y * Math.PI / 30.0)) * 2.0 / 3.0;
        return ret;
    }

    private static double transformLon(double x, double y) {
        double ret = 300.0 + x + 2.0 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * Math.sqrt(Math.abs(x));
        ret += (20.0 * Math.sin(6.0 * x * Math.PI) + 20.0 * Math.sin(2.0 * x * Math.PI)) * 2.0 / 3.0;
        ret += (20.0 * Math.sin(x * Math.PI) + 40.0 * Math.sin(x / 3.0 * Math.PI)) * 2.0 / 3.0;
        ret +=
                (150.0 * Math.sin(x / 12.0 * Math.PI) + 300.0 * Math.sin(x / 30.0 * Math.PI)) * 2.0 / 3.0;
        return ret;
    }

    /**
     * @param lat 纬度
     * @param lng 经度
     * @return
     */
    private static double[] delta(double lat, double lng) {
        double[] delta = new double[2];
        double a = 6378137.0;
        double ee = 0.00669342162296594323;
        double dLat = transformLat(lng - 105.0, lat - 35.0);
        double dLng = transformLon(lng - 105.0, lat - 35.0);
        double radLat = lat / 180.0 * Math.PI;
        double magic = Math.sin(radLat);
        magic = 1 - ee * magic * magic;
        double sqrtMagic = Math.sqrt(magic);
        delta[0] = (dLat * 180.0) / ((a * (1 - ee)) / (magic * sqrtMagic) * Math.PI);
        delta[1] = (dLng * 180.0) / (a / sqrtMagic * Math.cos(radLat) * Math.PI);
        return delta;
    }

}