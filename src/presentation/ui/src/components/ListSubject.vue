<template>
<div class="ListSubject">
  <h1>Les réponses au formulaire n°{{ form.id }}</h1>
  <el-table :data="Object.values(subjects)" style="width: 100%" stripe>
   <el-table-column
      type="selection"
      width="55">
    </el-table-column>
    <el-table-column
      label="Status">
      <template slot-scope="scope">
       <el-tag :type="scope.row.isValid ? 'success' : 'danger'">{{scope.row.isValid ? 'Validé' : 'Non validé'}}</el-tag>
      </template>
    </el-table-column>
    <el-table-column
      label="Opérations">
      <template slot-scope="scope">
       <el-button-group>
         <el-button @click="edit(scope.row.id)" type="primary" icon="el-icon-edit"></el-button>
         <el-button @click="remove(scope.row.id)" type="danger" icon="el-icon-delete"></el-button>
       </el-button-group>
      </template>
    </el-table-column>
  </el-table>
  <div style="margin-top: 20px">
    <el-button @click="add()" type="primary">Ajouter une réponse</el-button>
  </div>
</div>
</template>

<script>
export default {
  name: 'ListSubject',
  data () {
    return {
      form: {
        id: 0,
        name: 'Étude de l IUT d Arles',
        description: 'info2 - décembre 2018'
      },
      subjects: {
        0: {
          id: 0,
          isValid: false
        },
        1: {
          id: 1,
          isValid: true
        },
        2: {
          id: 2,
          isValid: false
        }
      }
    }
  },
  methods: {
    add: function () {
      console.log('Add subject')
      this.$router.push({name: 'AnswerForm', params: { id: 'new' }})
    },
    remove: function (id) {
      console.log('Remove subject : ' + id)
    },
    edit: function (id) {
      console.log('Edit subject : ' + id)
      this.$router.push({name: 'AnswerForm', params: { id: id }})
    }
  }
}
</script>

<style scoped>
</style>
