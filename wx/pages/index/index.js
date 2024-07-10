import mqtt from '../../utils/mqtt.js';
const aliyunOpt = require('../../utils/aliyun/aliyun_connect.js');

let that = null;
Page({
  data: {
    phoneNumber: "",
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
      productKey: '', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
      deviceName: '', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
      deviceSecret: '', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
      regionId: '', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
      pubTopic: '', //发布消息的主题
      subTopic: '', //订阅消息的主题
    },
    provinces: [
      ['京', '沪', '粤', '津', '冀', '晋', '蒙', '辽', '吉', '黑'],
      ['苏', '浙', '皖', '闽', '赣', '鲁', '豫', '鄂', '湘'],
      ['桂', '琼', '渝', '川', '贵', '云', '藏'],
      ['陕', '甘', '青', '宁', '新'],
    ],
    // 车牌输入
    numbers: [
      ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"],
      ["Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"],
      ["A", "S", "D", "F", "G", "H", "J", "K", "L"],
      ["Z", "X", "C", "V", "B", "N", "M"]
    ],
    carnum: [],
    showNewPower: false,
    KeyboardState: false
  },
  onPhoneNumberInput: function(e) {
    this.setData({
      phoneNumber: e.detail.value,
      carNumber: e.detail.value
    });
  },
  bindChoose(e) {
    if (!this.data.carnum[6] || this.data.showNewPower) {
      var arr = [];
      arr[0] = e.target.dataset.val;
      this.data.carnum = this.data.carnum.concat(arr)
      this.setData({
        carnum: this.data.carnum
      })
    }
    if (this.data.carnum[6]) {
      this.setData({
        showNewPower: true,
        KeyboardState: true
      })
    }
  },
  bindDelChoose() {
    if (this.data.carnum.length != 0) {
      this.data.carnum.splice(this.data.carnum.length - 1, 1);
      this.setData({
        carnum: this.data.carnum
      })
    }
  },
  showPowerBtn() {
    this.setData({
      showNewPower: true,
      KeyboardState: true
    })
  },
  closeKeyboard() {
    this.setData({
      KeyboardState: false
    })
  },
  openKeyboard() {
    this.setData({
      KeyboardState: true
    })
  },
  //清空按钮
  deleteAll() {
    this.setData({
      carnum: [],
    })
  },
  submitNumber: function() {
    const phoneNumber = this.data.phoneNumber;
    var carno = this.data.carnum;
    var carnonew = carno.join('');
    if (!phoneNumber) {
      wx.showToast({
        title: '请输入手机号',
        icon: 'none',
        duration: 2000
      });
      return;
    }
    if (this.data.carnum.length < 7) {
      wx.showToast({
        title: '请输入完整的车牌!',
        icon: 'none',
        duration: 2000,
      });
      return;
    }
    if (this.data.carnum[6]) {
      console.log(carnonew);
    }
    
    // 发送手机号到云端
    this.sendNumber(phoneNumber, carnonew);
    wx.navigateTo({
      url: '../logs/logs'
    })
  },
  sendNumber: function(phoneNumber, carNumber) {
    this.sendCommond( { bindWx: { phone:phoneNumber, carSign:carNumber }} );
  },
  onLoad: function () {
    this.setData({
      carnum: ['鄂'],
    }),
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
  sendCommond(params) {
    let sendData = {
      params: params
    };

    //此函数是订阅的函数，因为放在访问服务器的函数后面没法成功订阅topic，因此把他放在这个确保订阅topic的时候已成功连接服务器
    //订阅消息函数，订阅一次即可 如果云端没有订阅的话，需要取消注释，等待成功连接服务器之后，在随便点击（开灯）或（关灯）就可以订阅函数
    /*this.data.client.subscribe(this.data.aliyunInfo.subTopic,function(err){
      if(!err){
        console.log("订阅成功");
      }
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