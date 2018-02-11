<template>
<div class="EditClosedQuestion">
  <el-table :data="Object.values(question.choices)" style="width: 100%" stripe>
    <el-table-column
      label="Label"
      width="500">
      <template slot-scope="scope">
        <el-input placeholder="Label" v-model="scope.row.label"></el-input>
      </template>
    </el-table-column>
    <el-table-column
      label="Opérations">
      <template slot-scope="scope">
       <el-button @click="remove(scope.row.id)" type="danger" icon="el-icon-delete"></el-button>
      </template>
    </el-table-column>
  </el-table>
  <div style="margin-top: 20px">
    <el-input placeholder="Label" v-model="new_choice"></el-input>
    <el-button @click="add()" type="primary">Ajouter un choix</el-button>
  </div>
</div>
</template>

<script>
export default {
  name: 'EditClosedQuestion',
  props: {
    question: Object,
    required: true
  },
  data: function () {
    return {
      new_choice: '',
      new_id: 0
    }
  },
  created: function () {
    var keys = Object.keys(this.question.choices)
    if (keys.length !== 0) {
      this.new_id = Math.max(...keys) + 1
    }
  },
  methods: {
    add: function () {
      if (this.new_choice !== '') {
        this.$set(this.question.choices, this.new_id, {id: this.new_id, label: this.new_choice})
        this.new_id = this.new_id + 1
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
