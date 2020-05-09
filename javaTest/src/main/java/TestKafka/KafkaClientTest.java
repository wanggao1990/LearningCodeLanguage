package TestKafka;


import org.apache.kafka.clients.consumer.ConsumerRecord;
import org.apache.kafka.clients.consumer.ConsumerRecords;
import org.apache.kafka.clients.consumer.KafkaConsumer;
import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.Producer;
import org.apache.kafka.clients.producer.ProducerRecord;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Properties;



public class KafkaClientTest {

    public final static String TOPIC = "aeroscope-log";

    public static void main(String[] args) {

//        new Thread(new Runnable() {
//            @Override
//            public void run() {
//                RunKafkaConsumer();
//            }
//        }).start();

        RunKafkaProduce();
    }


   static private void RunKafkaProduce(){

        Properties props = new Properties();
        props.put("bootstrap.servers", "192.168.3.172:9092");
        props.put("acks", "all");
        props.put("retries", 0);
        props.put("batch.size", 16384);
        props.put("linger.ms", 1);
        props.put("buffer.memory", 33554432);
        props.put("key.serializer", "org.apache.kafka.common.serialization.StringSerializer");
        props.put("value.serializer", "org.apache.kafka.common.serialization.StringSerializer");

        Producer<String, String> producer = new KafkaProducer<>(props);
        for (int i = 0; i < 2; i++) {
            producer.send(new ProducerRecord<String, String>("foo", Integer.toString(i), Integer.toString(i)));
            producer.send(new ProducerRecord<String, String>("aeroscope-log", Integer.toString(i), Integer.toString(i)));
        }
       System.out.println("消息已推送结束");
        producer.close();


    }

    static private void RunKafkaConsumer() {

        System.out.println("开启消费者线程");

        Properties props = new Properties();
        props.put("bootstrap.servers", "192.168.3.172:9092");
        props.put("group.id", "test");
        props.put("enable.auto.commit", "true");
        props.put("auto.commit.interval.ms", "1000");
        props.put("key.deserializer", "org.apache.kafka.common.serialization.StringDeserializer");
        props.put("value.deserializer", "org.apache.kafka.common.serialization.StringDeserializer");
        KafkaConsumer<String, String> consumer = new KafkaConsumer<>(props);
        consumer.subscribe(Arrays.asList("foo", "bar","aeroscope-log","test"));
        while (true) {
            ConsumerRecords<String, String> records = consumer.poll(100);
            for (ConsumerRecord<String, String> record : records)
                System.out.printf("offset = %d, key = %s, value = %s%n", record.offset(), record.key(), record.value());
        }
    }
}
