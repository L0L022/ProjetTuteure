import Vue from 'vue'
import Router from 'vue-router'
import ListForm from '@/components/ListForm'
import EditForm from '@/components/EditForm'
import ViewForm from '@/components/ViewForm'
import AnswerForm from '@/components/AnswerForm'
import ListSubject from '@/components/ListSubject'

Vue.use(Router)

export default new Router({
  routes: [
    { path: '/',
      redirect: { name: 'ListForm' }
    },
    {
      path: '/list',
      name: 'ListForm',
      component: ListForm
    },
    {
      path: '/edit/:id',
      name: 'EditForm',
      component: EditForm,
      props: true
    },
    {
      path: '/view/:id',
      name: 'ViewForm',
      component: ViewForm,
      props: true
    },
    {
      path: '/answer/:formId/:subjectId',
      name: 'AnswerForm',
      component: AnswerForm,
      props: true
    },
    {
      path: '/subjects/:id',
      name: 'ListSubject',
      component: ListSubject,
      props: true
    }
  ]
})
