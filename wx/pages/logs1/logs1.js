// logs.js
const util = require('../../utils/util.js')

Page({
  data: {
    data: [],
    texts: []
  },
  onLoad() {
    const texts = [
      '您现在位于停车场南入口'
    ];
    const times = [
      '2024/7/7 21:26'
    ];

    this.setData({
      times: times,
      texts: texts
    });
  },
  parkings() {
    wx.redirectTo({
      url: '../logs2/logs'
    })
  },
})