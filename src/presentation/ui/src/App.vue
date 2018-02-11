<template>
 <el-container id="app">
  <el-main>
   <el-button @click="$router.back()">Retour</el-button>
   <router-view/>
  </el-main>
 </el-container>
</template>

<script>
export default {
  name: 'App'
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
