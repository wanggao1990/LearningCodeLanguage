# -*- coding: gb2312 -*-
"""
Know more, visit my Python tutorial page: https://morvanzhou.github.io/tutorials/
My Youtube Channel: https://www.youtube.com/user/MorvanZhou

Dependencies:
tensorflow: 1.1.0
matplotlib
numpy
"""
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data

mnist = input_data.read_data_sets('MNIST_data', one_hot=True)

def add_layer(inputs, in_size, out_size, activation_function=None):
    Weights = tf.Variable(tf.random_normal([in_size, out_size]))
    biases = tf.Variable(tf.zeros([1, out_size]) + 0.1)
    Wx_plus_b = tf.matmul(inputs, Weights) + biases
    if activation_function is None:
        outputs = Wx_plus_b
    else:
        outputs = activation_function(Wx_plus_b)
    return outputs

def computer_accuracy(v_xs,v_ys):
    global prediction
    y_pre = sess.run(prediction, feed_dict={xs: v_xs})
    correct_predicttion = tf.equal(tf.argmax(y_pre, 1), tf.argmax(v_ys, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_predicttion, tf.float32))
    result = sess.run(accuracy, feed_dict={xs: v_xs, ys: v_ys})
    return result

### define layers
def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(initial)

def bias_variable(shape):
    initial=tf.constant(0.1,shape=shape)
    return tf.Variable(initial)

def conv2d(x,W):
    return tf.nn.conv2d(x,W,strides=[1,1,1,1], padding='SAME')

def max_pool_2x2(x):
    # kernel size(2,2)
    return tf.nn.max_pool(x,ksize=[1,2,2,1],strides=[1,2,2,1],padding="SAME")

# define palceholder for inputs to network
xs = tf.placeholder(tf.float32, [None,784])
ys = tf.placeholder(tf.float32, [None,10])
keep_prob = tf.placeholder(tf.float32)
x_image = tf.reshape(xs,[-1,28,28,1])
# print(x_image.shape)  #[-1,28,28,1]

### Network definaition
W_conv1 = weight_variable([5,5,1,32])   # 卷积核，batch =[5,5], in_size=1(和图像通道数一致), out_size=32
b_conv1 = weight_variable([32])         # 理论上应该是1，多个共享一个bias
conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)  # [-1,28,28,32]
h_pool1 = max_pool_2x2(conv1)                           # [-1,14,14,32]

W_conv2 = weight_variable([5,5,32,64])  #
b_conv2 = weight_variable([64])         #
conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)  # [-1,14,14,64]
h_pool2 = max_pool_2x2(conv2)                           # [-1,7,7,64]

W_fc1 = weight_variable([7*7*64,1024])
b_fc1 = bias_variable([1024])
h_pool2_flat = tf.reshape(h_pool2,[-1,7*7*64]) # [-1,7,7,64] --> [-1,7*7*64]
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat,W_fc1) + b_fc1)
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

W_fc2 = weight_variable([1024,10])
b_fc2= bias_variable([10])
prediction = tf.nn.softmax(tf.matmul(h_fc1_drop,W_fc2) + b_fc2)


### loss and traner
cross_entropy = tf.reduce_mean(-tf.reduce_sum(ys* tf.log(prediction),
                                              reduction_indices=[1]))
train_step = tf.train.AdamOptimizer(1e-3).minimize(cross_entropy)


# training
with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())

    for i in range(1000):
        # training
        batch_x, batch_y = mnist.train.next_batch(100)
        sess.run(train_step, feed_dict={xs: batch_x, ys:batch_y, keep_prob:0.5})
        if i % 50 == 0:
            print(computer_accuracy(mnist.test.images, mnist.test.labels))

