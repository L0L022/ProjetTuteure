<template>
<div class="EditClosedQuestion">
  <el-table :data="Object.values(question.choices)" style="width: 100%">
    <el-table-column label="Label" width="500">
      <template slot-scope="scope">
        <el-input placeholder="Label" v-model="scope.row.label"></el-input>
      </template>
    </el-table-column>
    <el-table-column label="Opérations">
      <template slot-scope="scope">
       <el-button @click="remove(scope.row.id)" type="danger" icon="el-icon-delete"></el-button>
      </template>
    </el-table-column>
  </el-table>
  <div style="margin-top: 20px">
    <el-col :span="16">
      <el-input @keyup.native.enter="add()" placeholder="Label du nouveau choix" v-model="new_choice"></el-input>
    </el-col>
    <el-col :span="8">
      <el-button @click="add()" type="primary">Ajouter un choix</el-button>
    </el-col>
  </div>
</div>
</template>

<script>
export default {
  name: 'EditClosedQuestion',
  props: {
    services: {
      type: Object,
      required: true
    },
    question: {
      type: Object,
      required: true
    }
  },
  data () {
    return {
      new_choice: ''
    }
  },
  created: function () {
    console.log(this.question.choices)
  },
  methods: {
    add: function () {
      if (this.new_choice !== '') {
        var me = this
        this.services.call('takeChoiceId', {}, function (data) {
          me.$set(me.question.choices, data['id'], {
            id: data['id'],
            label: me.new_choice
          })
          me.new_choice = ''
        })
      }
    },
    remove: function (id) {
      this.$delete(this.question.choices, id)
    }
  }
}
</script>

<style scoped>
</style>
