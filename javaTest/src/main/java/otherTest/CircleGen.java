package otherTest;


import org.joda.time.DateTime;
import org.joda.time.format.DateTimeFormatter;

public class CircleGen {

    private double[] center;          // 中心(x,y)
    private double radius = 10;      // 半径 经纬度距离
    private double startAngle = 0;   // 起始角度
    private double delta = 10;       // 步进角度

    private final double  ANG_PI = Math.PI/180;

    CircleGen(double[] center, double radius, double delta ){
        this.center = center;
        this.radius = radius;
        this.delta = delta;
    }

    public double[] getNetPoint(){
        startAngle += delta;
        if(startAngle >= 360 )
            startAngle = 0;

        double dx = this.radius * Math.cos(startAngle*ANG_PI);
        double dy = this.radius * Math.sin(startAngle*ANG_PI);

        double x = this.center[0] + dx;
        double y = this.center[1] + dy;

        return new double[]{x,y};
    }

    public static void main(String[] args) {

//        System.out.println((DateTime.now().toGregorianCalendar().toZonedDateTime()));
        System.out.println(DateTime.now());

//        CircleGen cg = new CircleGen(new double[]{0,0}, 10,10);
//
//        for(int i = 0;i < 360/10; i ++) {
//            double[] pt = cg.getNetPoint();
//            System.out.printf("%f,%f \n", pt[0], pt[1]);
//        }
    }
}
