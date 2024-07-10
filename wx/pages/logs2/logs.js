// logs.js
const util = require('../../utils/util.js')

Page({
  data: {
    data: [],
    texts: []
  },
  onLoad() {
    const texts = [
      '前方第一个路口左转',
      '您现在位于停车场南入口'
    ];
    this.setData({
      texts: texts
    });
  },
  parkings() {
    wx.redirectTo({
      url: '../logs3/logs'
    })
  },
})