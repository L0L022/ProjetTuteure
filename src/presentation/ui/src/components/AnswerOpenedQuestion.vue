<template>
<div class="AnswerOpenedQuestion">
  <el-input v-for="i in question.nb_words" :key="i" v-model="answer.words[i-1]"></el-input>
</div>
</template>

<script>
export default {
  name: 'AnswerOpenedQuestion',
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
