// logs.js
const util = require('../../utils/util.js')

Page({
  data: {
    data: [],
    texts: []
  },
  onLoad() {
    const texts = [
      '前方第一个岔路口左转',
      '前方第一个岔路口右转',
      '前方第二个岔路口右转',
      '前方第一个岔路口左转',
    ];
   

    this.setData({
      times: times,
      texts: texts
    });
  },
  parkings() {
    wx.redirectTo({
      url: '../logs1/logs1'
    })
  },
})