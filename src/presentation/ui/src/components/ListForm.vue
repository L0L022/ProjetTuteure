<template>
<div class="ListForm">
  <h1>Vos enquêtes</h1>
  <el-table :data="Object.values(forms)" style="width: 100%" stripe>
    <el-table-column label="N°" prop="id" width="55">
    </el-table-column>
    <el-table-column label="Nom" prop="name">
    </el-table-column>
    <el-table-column label="Description" prop="description">
    </el-table-column>
    <el-table-column label="Opérations">
      <template slot-scope="scope">
       <el-button-group>
         <el-tooltip content="Voir l'enquête">
           <el-button @click="viewForm(scope.row.id)" type="primary" icon="el-icon-view"></el-button>
         </el-tooltip>
         <el-tooltip content="Voir les individus liés à l'enquête">
           <el-button @click="viewAnswers(scope.row.id)" type="primary" icon="el-icon-tickets"></el-button>
         </el-tooltip>
         <el-tooltip content="Modifier l'enquête">
           <el-button @click="edit(scope.row.id)" type="primary" icon="el-icon-edit"></el-button>
         </el-tooltip>
         <el-tooltip content="Supprimer l'enquête">
           <el-button @click="remove(scope.row.id)" type="danger" icon="el-icon-delete"></el-button>
         </el-tooltip>
       </el-button-group>
      </template>
    </el-table-column>
  </el-table>
  <div style="margin-top: 20px">
    <el-button @click="add()" type="primary">Ajouter une enquête</el-button>
  </div>
</div>
</template>

<script>
export default {
  name: 'ListForm',
  props: {
    services: {
      type: Object,
      required: true
    }
  },
  data () {
    return {
      forms: {}
    }
  },
  created: function () {
    this.refresh()
  },
  methods: {
    refresh: function () {
      console.log('refresh')
      var me = this
      this.services.call('listForms', {}, function (data) {
        me.forms = data.forms
      })
    },
    add: function () {
      console.log('Add form')
      this.$router.push({
        name: 'EditForm',
        params: {
          id: 'new'
        }
      })
    },
    remove: function (id) {
      console.log('Remove form : ' + id)
      var me = this
      this.services.call('deleteForm', {id: id}, function (data) {
        me.refresh()
      })
    },
    edit: function (id) {
      console.log('Edit form : ' + id)
      this.$router.push({
        name: 'EditForm',
        params: {
          id: id
        }
      })
    },
    viewForm: function (id) {
      console.log('View form : ' + id)
      this.$router.push({
        name: 'ViewForm',
        params: {
          id: id
        }
      })
    },
    viewAnswers: function (id) {
      console.log('View answers : ' + id)
      this.$router.push({
        name: 'ListSubject',
        params: {
          id: id
        }
      })
    }
  }
}
</script>

<style scoped>
</style>
