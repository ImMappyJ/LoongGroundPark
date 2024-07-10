// logs.js


Page({
  data: {
    data: [],
    texts: []
  },
  onLoad() {
    const texts = [
      '您现在位于停车场南入口'
    ];
    this.setData({
      texts: texts
    });
  },
  parkings() {
    wx.redirectTo({
      url: '../logs2/logs'
    })
  },
})