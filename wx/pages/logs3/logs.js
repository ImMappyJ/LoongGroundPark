// logs.js

Page({
  data: {
    data: [],
    texts: []
  },
  onLoad() {
    const texts = [
      '前方第二个路口右转',
      '前方第一个路口左转',
      '您现在位于停车场南入口'
    ];

    this.setData({
      texts: texts
    });
  },
  parkings() {
    wx.redirectTo({
      url: '../logs4/logs'
    })
  },
})