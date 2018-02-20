<template>
<div class="AnswerForm">
  <h1>Édition du sujet n°{{ subject.id }} du formulaire n°{{ form.id }}</h1>
  Nom : {{ form.name }}<br>
  Description : {{ form.description }}<br>
  Est validé : <el-switch v-model="subject.isValid"></el-switch><br>
  <el-table
      :data="Object.values(form.questions)"
      default-expand-all
      style="width: 100%">
       <el-table-column type="expand">
         <template slot-scope="scope">
           <AnswerClosedQuestion v-if="(scope.row.type === 'unique') || (scope.row.type ==='multiple')" :question="scope.row" :answer="subject.answers[scope.row.id]"></AnswerClosedQuestion>
           <AnswerOpenedQuestion v-if="scope.row.type === 'opened'" :question="scope.row" :answer="subject.answers[scope.row.id]"></AnswerOpenedQuestion>
         </template>
       </el-table-column>
      <el-table-column
        label="Titre"
        prop="title">
      </el-table-column>
  </el-table>
  <el-button @click="save()">Enregistrer</el-button>
</div>
</template>

<script>
import AnswerClosedQuestion from '@/components/AnswerClosedQuestion'
import AnswerOpenedQuestion from '@/components/AnswerOpenedQuestion'

export default {
  name: 'AnswerForm',
  props: {
    id: String,
    required: true
  },
  data () {
    return {
      types: [
        {
          value: 'multiple',
          label: 'Choix multiple'
        },
        {
          value: 'unique',
          label: 'Choix unique'
        },
        {
          value: 'opened',
          label: 'Ouverte'
        }
      ],
      form: {
        id: 0,
        name: 'Étude de l\'IUT d\'Arles',
        description: 'info2 - décembre 2018',
        questions: {
          0: {
            id: 0,
            title: 'Que pensez-vous quand je vous dis IUT ?',
            type: 'opened',
            nbAnswers: 10,
            choices: {}
          },
          1: {
            id: 1,
            title: 'Votre matière préférée',
            type: 'unique',
            nbAnswers: 0,
            choices: {
              0: {
                id: 0,
                label: 'Anglais'
              },
              1: {
                id: 1,
                label: 'Algo avancé'
              },
              2: {
                id: 2,
                label: 'Mathématiques'
              }
            }
          },
          2: {
            id: 2,
            title: 'Vos langages préférés',
            type: 'multiple',
            nbAnswers: 0,
            choices: {
              0: {
                id: 0,
                label: 'C++'
              },
              1: {
                id: 1,
                label: 'PHP'
              },
              2: {
                id: 2,
                label: 'BASH'
              }
            }
          }
        }
      },
      subject: {
        id: 0,
        isValid: false,
        answers: {
          0: {
            id: 0,
            words: ['un', 'deux', 'trois', 'quatre', 'cinq', 'six', 'sept', 'huit', 'neuf', 'dix']
          },
          1: {
            id: 1,
            choice: 2
          },
          2: {
            id: 2,
            choices: [
              0,
              2
            ]
          }
        }
      },
      new_question_title: '',
      new_question_id: 0
    }
  },
  created: function () {
    var keys = Object.keys(this.form.questions)
    if (keys.length !== 0) {
      this.new_question_id = Math.max(...keys) + 1
    }
  },
  methods: {
    add: function () {
      if (this.new_question_title !== '') {
        this.$set(this.form.questions, this.new_question_id, {id: this.new_question_id, title: this.new_question_title, type: '', nbAnswers: 0, choices: {}})
        this.new_question_id = this.new_question_id + 1
      }
    },
    remove: function (id) {
      this.$delete(this.form.questions, id)
    },
    save: function () {
      console.log('Save : ' + JSON.stringify(this.form))
    }
  },
  components: {
    AnswerClosedQuestion,
    AnswerOpenedQuestion
  }
}
</script>

<style scoped>
</style>
