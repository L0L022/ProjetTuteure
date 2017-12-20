
let navbar = {

    props: {
        formu: String,
        modif: String,
        upco: String,
        curentpage: String
    },

    template: `<div class="ui three item menu">
                        <a class="item" :class="formu" v-on:click="formulaire">Formulaire</a>
                        <a class="item" :class="modif" v-on:click="modification">Modification Page</a>
                        <a class="item" :class="upco" v-on:click="upcoming">Upcoming Events</a>
                </div>`
    ,

    methods: {

        formulaire: function () {
            this.$emit('formulaire')
        },

        modification: function () {
            this.$emit('modification')
        },

        upcoming: function () {
            this.$emit('upcoming')
        }
    }
};

let shortformspage = {
    props: {
        title:String,
        description: String,
        id: Number,
        idasupprimer: Number
    },
    template:`<div>
                <p>{{id}}</p>
                <p>{{ title }}</p>
                
                <p>
                {{ description }} 
                <input type="button" name="supression" value="supression" @click="suppression">
                <input type="button" name="modifcation" value="modifcation">
                <input type="button" name="reponse" value="reponse" ><br/><br/> 
                </p>
</div>`,
    methods:{
        suppression: function(){
            this.$parent.$parent.$data.idasupprimer=this.id ;
            this.$emit('suppression')
        }
    }
};

let formspage = {
    props: {question: Object,
        idasupprimer: Number
        },
    components: { shortformspage },
    template: `<div>
                <div v-for="question in question">
                    <shortformspage @suppression="suppression" :idasupprimer="idasupprimer" :title="question.title" :description="question.description" :id="question.id" ></shortformspage>
                </div>
                <input v-on:click="newform" type="button"  value="nouveau formulaire" >
                
</div>`,
    methods:{
        suppression: function(){
            this.$emit('suppression')
        },
        newform: function(){
            this.$parent.$data.curentpage="newform"
        }
    }
};

let editclosedquestion = {
  template:`<div>
                <input type="text" value="une premiere réponse">
                <input type="button" value="supprimer une réponse">
            </div>`
};

let editopenquestion = {
    template: `<div>
                    <input type="text" value="0">
               </div>`
};

let editquestion = {
    components: { editopenquestion, editclosedquestion },
    data() {
        return {
            typequestion:""
        }
    },
    template: `<div>
                    <select v-model="typequestion">
                        <option value="QO">Question à choix ouvert</option>
                        <option value="QM">Question à choix multiple</option>
                        <option value="QC">Question à choix unique</option>  
                    </select>
                    <input type="text" value="titre d'une question">
                    <input type="button" value="supprimer">
                    <editopenquestion v-if="typequestion === 'QO' "></editopenquestion>
                    <editclosedquestion v-if ="typequestion === 'QM'"></editclosedquestion>
                    <editclosedquestion v-else-if ="typequestion === 'QC'"></editclosedquestion>
               </div>`


};

let editformspage = {
    components:{ editquestion },
    props:{
      title: String
    },
    template: `<div>
                    <input type="text" value="title">
                    <input type="text" value="description">
                    <editquestion></editquestion>
                    <input type="button" value="nouvelle question">
               </div>`
};

new Vue ({
    el: '#app' ,
    components: { navbar, formspage, editformspage },
    data: {
        curentpage: "formulaire",
        formu: "active",
        modif: "",
        upco: "",

        title: "titre d'un formulaire",
        description: "descriptionx formulaire",

        question:{
            0:{
                id: 0,
                title: "Le premier questionnaire",
                description: "la description du premier questionnaire"
            },
            1:{
                id: 1,
                title: "Le second questionnaire",
                description: "la description du second questionnaire"
            },
            2:{
                id: 2,
                title: "Le troisième questionnaire",
                description: "la description du troisième questionnaire"
            }
        },
        idasupprimer: -1,
        title: "Un titre de formulaire"
    },
    methods: {
        formulaire: function(){
            this.formu="active",
            this.modif="",
            this.upco="",
            this.curentpage="formulaire"
        },
        modification: function(){
            this.upco = " " ,
            this.formu = " " ,
            this.modif = "active",
            this.curentpage = "modification"
        },
        upcoming: function(){
            this.formu=" ",
            this.modif=" ",
            this.upco="active",
            this.curentpage="upcoming"
        },
        suppression: function(){
            delete this.question.idasupprimer;

        }
    }
})