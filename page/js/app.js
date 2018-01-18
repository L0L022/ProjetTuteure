
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
    props:{
        reponse: Object,
        newtab: Object
    },
  template:`<div>
                <input type="button" value="Ajouter une réponse" @click="ajtrep">
                <br>
                
                <div v-for="reponse in reponse">
                    <input type="text" :value='reponse'>
                    <input type="button" value="supprimer une réponse">
                </div>
                <div >
                    <input type="text" value="une premiere réponse">
                    <input type="button" value="supprimer une réponse">
                </div>
            </div>`,
    methods:{
        ajtrep: function(){
            this.newtab ++
        }
    }
};

let editopenquestion = {
    template: `<div>
                    <input type="text" value="0">
               </div>`
};

let editquestion = {
    components: { editopenquestion, editclosedquestion },
    props: {
        titlequest: {type: String, default: "titre de votre question"},
        typequest: {type: String, default: 'QO'    },
        reponse: {type: Object, default: function(){ return } },
        newtab: Object

    },
    template: `<div>
                    <select v-model="typequest" value="typequest">
                        <option value="QO">Question à choix ouvert</option>
                        <option value="QM">Question à choix multiple</option>
                        <option value="QC">Question à choix unique</option>  
                    </select>
                    
                    <input type="text" :value="titlequest">
                    
                    <input type="button" value="supprimer">
                    
                    <editopenquestion v-if="typequest === 'QO' " :newtab="newtab"></editopenquestion>
                    <editclosedquestion v-if ="typequest === 'QM'" :reponse="reponse" :newtab="newtab"></editclosedquestion>
                    <editclosedquestion v-else-if ="typequest === 'QC'" :reponse="reponse" :newtab="newtab"></editclosedquestion>
                    <br><br>
               </div>`


};

let editformspage = {
    components:{ editquestion },
    props:{
      title: String,
        tabloadform: Object

    },
    template: `<div>
                    <input type="text" value="title">
                    <input type="text" value="description">
                    <br><br>
                    <editquestion v-if="Object.keys(this.tabloadform).length === 0"></editquestion>
                    <div  v-for="tabloadform in tabloadform" v-else>
                        <editquestion :titlequest="tabloadform.titlequest" :typequest="tabloadform.typequest" :reponse="tabloadform.reponse" ></editquestion>
                    </div>
                    
                    <input type="button" value="nouvelle question" @click="newquest">
                    
                    <input type="button" value="sauver le formulaire" @click="save">
               </div>`,
    methods:{
        save: function(){
            this.$parent.$data.newtab = this.$parent.$data.tabloadform
        },
        newquest: function(){
            this.$emit('ajtquest')
        }
    }
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
        tabloadform:{
            0:{
                id: 0,
                titlequest:"Une première question a choix ouvert charger",
                typequest:"QO"
            },
            1:{
                id: 1,
                titlequest:"Une seconde question a choix multiple charger",
                typequest:'QM',
                reponse:{
                    0: "ceci est une prémière réponse",
                    1: "ceci est une seconde réponse"
                }
            }
        },
        newtab: {}


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

        },
        tab: function(){
            console.log(Object.keys(this.tabloadform).length === 0)
        },
        ajtquest: function (){
            this.tabloadform.push({'Object.keys(this.tabloadform).length': {id:Object.keys(this.tabloadform).length} })
        }
    }
})