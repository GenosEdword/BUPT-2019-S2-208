

Page({


  openlight:
    function sendCmd(id, data) {
      var devicedConncted
      wx.request({
        url: "https://api.heclouds.com/cmds?device_id=577092705",
        header: {
          'content-type': 'application/json',
          "api-key": '2sSrATDl=BmqF0eSVzv4kNN234M='
        },
        data: "1",
        method: 'POST',
        success(res) {
          console.log(res)
        },
        fail(res) {
          console.log("请求失败")
          devicedConncted = fales
        },
        complete() {
          if (devicedConncted) {
            console.log("0")
            return 0
          } else {
            console.log("complete no")
            return 1
          }
        }
      })
    },



  closelight:
    function sendCmd(id, data) {
      var devicedConncted
      wx.request({
        url: "https://api.heclouds.com/cmds?device_id=577092705",
        header: {
          'content-type': 'application/json',
          "api-key": '2sSrATDl=BmqF0eSVzv4kNN234M='
        },
        data: "0",
        method: 'POST',
        success(res) {
          console.log(res)
        },
        fail(res) {
          console.log("请求失败")
          devicedConncted = ture
        },
        complete() {
          if (devicedConncted) {
            console.log("1")
            return 1
          } else {
            console.log("complete no")
            return 0
          }
        }
      })
    },


  /**
  * 生命周期函数--监听页面加载
  */
  onLoad: function (options) {

  },

  /**
  * 生命周期函数--监听页面初次渲染完成
  */
  onReady: function () {

  },

  /**
  * 生命周期函数--监听页面显示
  */
  onShow: function () {

  },

  /**
  * 生命周期函数--监听页面隐藏
  */
  onHide: function () {

  },

  /**
  * 生命周期函数--监听页面卸载
  */
  onUnload: function () {

  },

  /**
  * 页面相关事件处理函数--监听用户下拉动作
  */
  onPullDownRefresh: function () {

  },

  /**
  * 页面上拉触底事件的处理函数
  */
  onReachBottom: function () {

  },

  /**
  * 用户点击右上角分享
  */
  onShareAppMessage: function () {

  }
})