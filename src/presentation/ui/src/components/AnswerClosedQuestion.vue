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
  }
}
</script>

<style scoped>
</style>
