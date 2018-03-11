import Vue from 'vue'
import App from './App'
import router from './router'

import ElementUI from 'element-ui'
import locale from 'element-ui/lib/locale/lang/fr'
import 'element-ui/lib/theme-chalk/index.css'

import VueCharts from 'vue-charts'

Vue.use(ElementUI, { locale })
Vue.use(VueCharts)

Vue.config.productionTip = false

/* eslint-disable no-new */
new Vue({
  el: '#app',
  router,
  components: { App },
  template: '<App/>'
})