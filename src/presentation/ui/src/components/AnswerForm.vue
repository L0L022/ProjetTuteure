<template>
<div class="AnswerForm" v-if="!loading">
  <h1>Édition du sujet n°{{ subject.id }} du formulaire n°{{ form.id }}</h1> Nom : {{ form.name }}<br> Description : {{ form.description }}<br> Est validé :
  <el-switch v-model="subject.is_valid"></el-switch><br>
  <el-table :data="Object.values(form.questions)" default-expand-all style="width: 100%">
    <el-table-column type="expand">
      <template slot-scope="scope">
        <AnswerClosedQuestion v-if="(scope.row.type === 'unique') || (scope.row.type ==='multiple')" :question="scope.row" :answer="subject.answers[scope.row.id]"></AnswerClosedQuestion>
        <AnswerOpenedQuestion v-if="scope.row.type === 'opened'" :question="scope.row" :answer="subject.answers[scope.row.id]"></AnswerOpenedQuestion>
      </template>
    </el-table-column>
    <el-table-column label="Titre" prop="title">
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
    subjectId: {
      required: true
    },
    formId: {
      required: true
    },
    services: {
      type: Object,
      required: true
    }
  },
  data () {
    return {
      types: [{
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
        name: '',
        description: '',
        questions: {}
      },
      subject: {
        id: 0,
        is_valid: false,
        answers: {}
      },
      new_question_title: '',
      new_question_id: 0,
      loading: true
    }
  },
  created: function () {
    var me = this
    this.services.call('getForm', {
      id: this.formId
    }, function (data) {
      console.log('getForm')
      me.$set(me, 'form', data)
      me.refresh()
    })
  },
  methods: {
    refresh: function () {
      console.log('refresh')
      var me = this
      this.loading = true
      if (this.subjectId === 'new') {
        this.subject.id = 'new'
        this.services.call('getNewSubject', {
          form: this.formId
        }, function (data) {
          console.log('getNewSubject')
          me.$set(me, 'subject', data)
          me.loading = false
        })
      } else {
        this.services.call('getSubject', {
          id: this.subjectId
        }, function (data) {
          console.log('getSubject')
          me.$set(me, 'subject', data)
          me.loading = false
        })
      }
    },
    save: function () {
      console.log('Save : ' + JSON.stringify(this.subject))
      var me = this
      if (this.subject.id === 'new') {
        this.services.call('takeSubjectId', {}, function (data) {
          me.subject.id = data['id']
          me.services.call('saveSubject', {form: me.form.id, subject: me.subject}, function (data) {
            me.$router.replace({
              name: 'AnswerForm',
              params: {
                id: me.subject.id
              }
            })
          })
        })
      } else {
        this.services.call('saveSubject', {form: me.form.id, subject: me.subject}, function (data) {
          me.refresh()
        })
      }
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
