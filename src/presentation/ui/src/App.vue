<template>
<el-container id="app">
  <el-main>
    <el-button @click="$router.back()">Retour</el-button>
    <router-view v-if="services !== null" :services="services"/>
  </el-main>
</el-container>
</template>

<script>
import Services from './assets/js/services'

export default {
  name: 'App',
  data () {
    return {
      services: null,
      loading: null
    }
  },
  created: function () {
    this.initServices()
  },
  methods: {
    initServices () {
      var app = this
      var services = new Services('ws://localhost:12345', function () {
        app.services = services
        app.loading.close()
      })
      this.loading = this.$loading({
        text: 'Connexion avec le serveur'
      })

      services.socket.onclose = function (event) {
        app.services = null
        app.loading.close()

        // See http://tools.ietf.org/html/rfc6455#section-7.4.1
        if (event.code !== 1000) {
          app.$alert('Connection avec le serveur terminée anormalement. Code d\'erreur : ' + event.code, 'Connection avec le serveur perdue', {
            confirmButtonText: 'Réessayer',
            callback: action => {
              app.initServices()
            }
          })
        }
      }
    }
  }
}
</script>

<style>
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
