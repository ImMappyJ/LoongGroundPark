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
      '前方第一个路口右转',
      '前方第二个路口右转',
      '前方第一个路口左转',
      '您现在位于停车场南入口',
    ];
    const times = [
      '2024/7/7 21:26',
      '2024/7/7 21:26',
      '2024/7/7 21:26',
      '2024/7/7 21:26',
      '2024/7/7 21:26',
    ];

    this.setData({
      times: times,
      texts: texts
    });
  }
})