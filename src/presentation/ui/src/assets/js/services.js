'use strict'

import QWebChannel from './qwebchannel'

export default class Services {
  constructor (uri, channelInitCallback) {
    this.socket = new WebSocket(uri)
    this.initChannel = false

    var me = this

    this.socket.onclose = function () {
      me.initChannel = false
      console.error('web channel closed.')
    }

    this.socket.onerror = function (error) {
      me.initChannel = false
      console.error('web channel error: ' + error)
    }

    this.socket.onopen = function () {
      me.channel = new QWebChannel(me.socket, function (channel) {
        me.initChannel = true
        console.log('channel ok')
        channelInitCallback(channel)
      })
    }
  }

  call (id, params, callback) {
    var me = this
    this.channel.objects.services.run(id, params, function (r) {
      if ('error' in r) {
        me.callError(r['error'])
      } else {
        callback(r)
      }
    })
  }

  callError (e) {
    console.error('services error: ' + e)
  }

  isValid () {
    return this.initChannel
  }
}
