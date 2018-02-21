<template>
<div class="AnswerClosedQuestion">
  <el-radio-group v-if="question.type === 'unique'" v-model="answer.choice">
    <el-radio v-for="c in question.choices" :label="c.id" :key="c.id">{{c.label}}</el-radio>
  </el-radio-group>
  <el-checkbox-group v-if="question.type === 'multiple'" v-model="answer.choices">
    <el-checkbox v-for="c in question.choices" :label="c.id" :key="c.id">{{c.label}}</el-checkbox>
  </el-checkbox-group>
</div>
</template>

<script>
export default {
  name: 'AnswerClosedQuestion',
  props: {
    question: {
      type: Object,
      required: true
    },
    answer: {
      type: Object,
      required: true
    }
  },
  data: function() {
    return {
      choices: []
    }
  },
  created: function() {
    var keys = Object.keys(this.question.choices)
    if (keys.length !== 0) {
      this.new_id = Math.max(...keys) + 1
    }
  },
  methods: {
    add: function() {
      if (this.new_choice !== '') {
        this.$set(this.question.choices, this.new_id, {
          id: this.new_id,
          label: this.new_choice
        })
        this.new_id = this.new_id + 1
      }
    },
    remove: function(id) {
      this.$delete(this.question.choices, id)
    }
  }
}
</script>

<style scoped>
</style>
