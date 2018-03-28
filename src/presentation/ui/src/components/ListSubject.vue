<template>
<div class="ListSubject">
  <h1>Les individus de l'enquête n°{{ id }}</h1>
  <el-table :data="Object.values(subjects)" style="width: 100%" stripe>
    <el-table-column label="N°" prop="id" width="55">
    </el-table-column>
    <el-table-column label="Status">
      <template slot-scope="scope">
       <el-tag :type="scope.row.is_valid ? 'success' : 'danger'">{{scope.row.is_valid ? 'Validé' : 'Non validé'}}</el-tag>
      </template>
    </el-table-column>
    <el-table-column label="Opérations">
      <template slot-scope="scope">
       <el-button-group>
         <el-button @click="edit(scope.row.id)" type="primary" icon="el-icon-edit"></el-button>
         <el-button @click="remove(scope.row.id)" type="danger" icon="el-icon-delete"></el-button>
       </el-button-group>
      </template>
    </el-table-column>
  </el-table>
  <div style="margin-top: 20px">
    <el-button @click="add()" type="primary">Ajouter un individu</el-button>
  </div>
</div>
</template>

<script>
export default {
  name: 'ListSubject',
  props: {
    id: {
      required: true
    },
    services: {
      type: Object,
      required: true
    }
  },
  data () {
    return {
      subjects: {}
    }
  },
  created: function () {
    this.refresh()
  },
  methods: {
    refresh: function () {
      console.log('refresh')
      var me = this
      this.services.call('listSubjects', {
        id: this.id
      }, function (data) {
        me.subjects = data.subjects
      })
    },
    add: function () {
      console.log('Add subject')
      this.$router.push({
        name: 'AnswerForm',
        params: {
          formId: this.id,
          subjectId: 'new'
        }
      })
    },
    remove: function (id) {
      console.log('Remove subject : ' + id)
      var me = this
      this.services.call('deleteSubject', {
        id: id
      }, function (data) {
        me.refresh()
      })
    },
    edit: function (id) {
      console.log('Edit subject : ' + id)
      this.$router.push({
        name: 'AnswerForm',
        params: {
          formId: this.id,
          subjectId: id
        }
      })
    }
  },
  watch: {
    id: function () {
      this.refresh()
    }
  }
}
</script>

<style scoped>
</style>
