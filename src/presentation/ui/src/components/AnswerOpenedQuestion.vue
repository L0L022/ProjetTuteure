<template>
<div class="AnswerOpenedQuestion">
  <el-input v-for="i in question.nbAnswers" :key="i" v-model="answer.words[i-1]"></el-input>
</div>
</template>

<script>
export default {
  name: 'AnswerOpenedQuestion',
  props: {
    question: Object,
    answer: Object,
    required: true
  }
}
</script>

<style scoped>
</style>
