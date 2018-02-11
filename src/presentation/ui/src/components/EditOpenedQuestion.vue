<template>
<div class="EditOpenedQuestion">
  <el-input-number v-model="question.nbAnswers" :min="1" :max="99"></el-input-number>
</div>
</template>

<script>
export default {
  name: 'EditOpenedQuestion',
  props: {
    question: Object,
    required: true
  }
}
</script>

<style scoped>
</style>
