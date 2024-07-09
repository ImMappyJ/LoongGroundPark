import mqtt from '../../utils/mqtt.js';
const aliyunOpt = require('../../utils/aliyun/aliyun_connect.js');

let that = null;
Page({
  data: {
    phoneNumber: "",
    motto: '智慧停车系统',
    receive: "",
    //设置温度值和湿度值 
    temperature: "",
    humidity: "",

    client: null, //记录重连的次数
    reconnectCounts: 0, //MQTT连接的配置
    options: {
      protocolVersion: 4, //MQTT连接协议版本
      clean: false,
      reconnectPeriod: 1000, //1000毫秒，两次重新连接之间的间隔
      connectTimeout: 30 * 1000, //1000毫秒，两次重新连接之间的间隔
      resubscribe: true, //如果连接断开并重新连接，则会再次自动订阅已订阅的主题（默认true）
      clientId: '',
      password: '',
      username: '',
    },

    aliyunInfo: {
      productKey: 'test', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
      deviceName: 'wechat', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
      deviceSecret: 'test', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
      regionId: 'cn-shanghai', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
      pubTopic: '/test/wechat/user/topic', //发布消息的主题
      subTopic: '/test/wechat/user/topic', //订阅消息的主题
    },
  },
  onPhoneNumberInput: function(e) {
    this.setData({
      phoneNumber: e.detail.value
    });
  },
  car: function() {
    const phoneNumber = this.data.phoneNumber;
    if (!phoneNumber) {
      wx.showToast({
        title: '请输入手机号',
        icon: 'none',
        duration: 2000
      });
      return;
    }
    
    // 发送手机号到云端
    this.sendPhoneNumber(phoneNumber);
    wx.navigateTo({
      url: '../carnumber/carnumber'
    })
  },
  sendPhoneNumber: function(phoneNumber) {
    this.sendCommond('register', { phoneNumber: phoneNumber });
  },
  bindViewTap() {
    wx.navigateTo({
      url: '../logs/logs'
    })
  },
  onLoad: function () {
    that = this;
    let clientOpt = aliyunOpt.getAliyunIotMqttClient({
      productKey: that.data.aliyunInfo.productKey,
      deviceName: that.data.aliyunInfo.deviceName,
      deviceSecret: that.data.aliyunInfo.deviceSecret,
      regionId: that.data.aliyunInfo.regionId,
      port: that.data.aliyunInfo.port,
    });

    console.log("get data:" + JSON.stringify(clientOpt));
    let host = 'wxs://' + clientOpt.host;

    this.setData({
      'options.clientId': clientOpt.clientId,
      'options.password': clientOpt.password,
      'options.username': clientOpt.username,
    })
    console.log("this.data.options host:" + host);
    console.log("this.data.options data:" + JSON.stringify(this.data.options));

    //访问服务器
    this.data.client = mqtt.connect(host, this.data.options);

    this.data.client.on('connect', function (connack) {
      wx.showToast({
        title: '连接成功'
      })
      console.log("连接成功");
    })

    //接收消息监听
    this.data.client.on("message", function (topic, payload) {
      //this.receive = payload;
      console.log(" 收到 topic:" + topic + " , payload :" + payload);
      that.setData({
        //转换成JSON格式的数据进行读取
        temperature: JSON.parse(payload).currentTemperature,
        humidity: JSON.parse(payload).read,
      })
      /*       wx.showModal({
              content: " 收到topic:[" + topic + "], payload :[" + payload + "]",
              showCancel: false,
            }); */
    })

    //服务器连接异常的回调
    that.data.client.on("error", function (error) {
      console.log(" 服务器 error 的回调" + error)

    })
    //服务器重连连接异常的回调
    that.data.client.on("reconnect", function () {
      console.log(" 服务器 reconnect的回调")

    })
    //服务器连接异常的回调
    that.data.client.on("offline", function (errr) {
      console.log(" 服务器offline的回调")
    })
  },

  onClickOpen() {
    that.sendCommond('set', 1);
  },
  onClickOff() {
    that.sendCommond('set', 0);
  },
  sendCommond(cmd, data) {
    let sendData = {
      cmd: cmd,
      data: data,
    };

    //此函数是订阅的函数，因为放在访问服务器的函数后面没法成功订阅topic，因此把他放在这个确保订阅topic的时候已成功连接服务器
    //订阅消息函数，订阅一次即可 如果云端没有订阅的话，需要取消注释，等待成功连接服务器之后，在随便点击（开灯）或（关灯）就可以订阅函数
    /*this.data.client.subscribe(this.data.aliyunInfo.subTopic,function(err){
      if(!err){
        console.log("订阅成功");
      };
      wx.showModal({
        content: "订阅成功",
        showCancel: false,
      })
    })  */


    //发布消息
    if (this.data.client && this.data.client.connected) {
      this.data.client.publish(this.data.aliyunInfo.pubTopic, JSON.stringify(sendData));
      console.log("************************")
      console.log(this.data.aliyunInfo.pubTopic)
      console.log(JSON.stringify(sendData))
    } else {
      wx.showToast({
        title: '请先连接服务器',
        icon: 'none',
        duration: 2000
      })
    }
  }
})