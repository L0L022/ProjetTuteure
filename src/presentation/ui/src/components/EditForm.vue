<template>
<div class="EditForm">
  <h1 v-if="form.id === 'new'">Édition d'un nouveau formulaire</h1>
  <h1 v-if="form.id !== 'new'">Édition du formulaire n°{{ form.id }}</h1>
  <el-input placeholder="Nom" v-model="form.name"></el-input>
  <el-input placeholder="Description" v-model="form.description"></el-input>
  <el-table :data="Object.values(form.questions)" default-expand-all style="width: 100%">
    <el-table-column type="selection" width="55">
    </el-table-column>
    <el-table-column type="expand">
      <template slot-scope="scope">
           <EditClosedQuestion v-if="(scope.row.type === 'unique') || (scope.row.type ==='multiple')" :question="scope.row" :services="services"></EditClosedQuestion>
           <EditOpenedQuestion v-if="scope.row.type === 'opened'" :question="scope.row"></EditOpenedQuestion>
         </template>
    </el-table-column>
    <el-table-column label="Type" width="200">
      <template slot-scope="scope">
          <el-select v-model="scope.row.type" placeholder="Type">
           <el-option
             v-for="item in types"
             :key="item.value"
             :label="item.label"
             :value="item.value">
           </el-option>
          </el-select>
         </template>
    </el-table-column>
    <el-table-column label="Titre" width="500">
      <template slot-scope="scope">
          <el-input placeholder="Titre" v-model="scope.row.title"></el-input>
        </template>
    </el-table-column>
    <el-table-column label="Opérations">
      <template slot-scope="scope">
         <el-button @click="remove(scope.row.id)" type="danger" icon="el-icon-delete"></el-button>
        </template>
    </el-table-column>
  </el-table>
  <el-col :span="8">
    <el-select v-model="new_question_type" placeholder="Type de la nouvelle question">
      <el-option v-for="item in types" :key="item.value" :label="item.label" :value="item.value">
      </el-option>
    </el-select>
  </el-col>
  <el-col :span="8">
    <el-input placeholder="Titre de la nouvelle question" v-model="new_question_title"></el-input>
  </el-col>
  <el-col :span="8">
    <el-button @click="add()">Nouvelle question</el-button>
  </el-col>
  <el-button @click="save()">Enregistrer</el-button>
</div>
</template>

<script>
import EditClosedQuestion from '@/components/EditClosedQuestion'
import EditOpenedQuestion from '@/components/EditOpenedQuestion'

export default {
  name: 'EditForm',
  props: {
    id: {
      required: true
    },
    services: {
      type: Object,
      required: true
    }
  },
  data() {
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
      new_question_title: '',
      new_question_type: null
    }
  },
  created: function() {
    this.refresh()
  },
  methods: {
    refresh: function() {
      console.log('refresh');
      if (this.id === 'new') {
        this.form.id = 'new'
      } else {
        var me = this
        this.services.call('getForm', {
          id: this.id
        }, function(data) {
          me.form = data
        })
      }
    },
    add: function() {
      if (this.new_question_title !== '' && this.new_question_type !== null) {
        var me = this
        this.services.call('takeQuestionId', {}, function(data) {
          me.$set(me.form.questions, data['id'], {
            id: data['id'],
            title: me.new_question_title,
            type: me.new_question_type,
            nbAnswers: 0,
            choices: {}
          })
        })
      }
    },
    remove: function(id) {
      this.$delete(this.form.questions, id)
    },
    save: function() {
      console.log('Save : ' + JSON.stringify(this.form))
      var me = this
      if (this.form.id === 'new') {
        this.services.call('takeFormId', {}, function(data) {
          me.form.id = data['id']
          me.services.call('saveForm', me.form, function(data) {
            me.$router.replace({
              name: 'EditForm',
              params: {
                id: me.form.id
              }
            })
          })
        })
      } else {
        this.services.call('saveForm', this.form, function(data) {
          me.refresh()
        })
      }
    }
  },
  watch: {
    id: function() {
      this.refresh()
    }
  },
  components: {
    EditClosedQuestion,
    EditOpenedQuestion
  }
}
</script>

<style scoped>
</style>
