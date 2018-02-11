<template>
<div class="ListForm">
  <h1>Vos formulaires</h1>
  <el-table :data="Object.values(forms)" style="width: 100%" stripe>
   <el-table-column
      type="selection"
      width="55">
    </el-table-column>
    <el-table-column
      label="Nom"
      prop="name">
    </el-table-column>
    <el-table-column
      label="Description"
      prop="description">
    </el-table-column>
    <el-table-column
      label="Opérations">
      <template slot-scope="scope">
       <el-button-group>
         <el-button @click="view(scope.row.id)" type="primary" icon="el-icon-view"></el-button>
         <el-button @click="edit(scope.row.id)" type="primary" icon="el-icon-edit"></el-button>
         <el-button @click="remove(scope.row.id)" type="danger" icon="el-icon-delete"></el-button>
       </el-button-group>
      </template>
    </el-table-column>
  </el-table>
  <div style="margin-top: 20px">
    <el-button @click="add()" type="primary">Ajouter un formulaire</el-button>
  </div>
</div>
</template>

<script>
export default {
  name: 'ListForm',
  data () {
    return {
      forms: {
        0: {
          'id': 0,
          'name': 'Onaliok hojgi uzadus iga rep ogiak tugid.',
          'description': 'Agsafjuc sog va talla ligus dorin azideelo no duhfuh cot taeca wocukof pa weti vahvap.'
        },
        3: {
          'id': 3,
          'name': 'Hemaba ezobej hub goses de.',
          'description': 'Vugi fos paswuv ib mezvu pu su jelsuw zouci wu hum za mari pitosom vozpuf be hapol.'
        }
      }
    }
  },
  methods: {
    add: function () {
      console.log('Add form')
    },
    remove: function (id) {
      console.log('Remove form : ' + id)
    },
    edit: function (id) {
      console.log('Edit form : ' + id)
      this.$router.push({name: 'EditForm', params: { id: id }})
    },
    view: function (id) {
      console.log('View form : ' + id)
      this.$router.push({name: 'ViewForm', params: { id: id }})
    }
  }
}
</script>

<style scoped>
</style>
