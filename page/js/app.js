
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
                <input type="button" name="modifcation" value="modifcation" @click="modifform">
                <input type="button" name="reponse" value="reponse" @click="subject"><br/><br/> 
                </p>
</div>`,
    methods:{
        suppression: function(){
            this.$parent.$parent.$data.idasupprimer=this.id ;
            this.$emit('suppression')
        },
        modifform: function(){
            this.$parent.$parent.$data.amodif= this.id;
            this.$emit('modifform')
        },
        subject: function(){
            this.$emit('subject')
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
               <shortformspage @modifform="modifform" @subject="subject" @suppression="suppression" :idasupprimer="idasupprimer" :title="question.title" :description="question.description" :id="question.id" ></shortformspage>
                </div>
                <input v-on:click="newform" type="button"  value="nouveau formulaire" >
                
</div>`,
    methods:{
        suppression: function(){
            this.$emit('suppression')
        },
        newform: function(){
            this.$parent.$data.curentpage="newform"
        },
        modifform: function(){
            this.$emit('modifform')
        },
        subject:function(){
            this.$emit('subject')
        }

    }
};

let editclosedquestion = {
    props:{
        reponse: Object
    },
  template:`<div>
                <input type="button" value="Ajouter une réponse" >
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
        reponse: {type: Object, default: function(){ return {} } }

    },
    template: `<div>
                    <select v-model="typequest" value="typequest">
                        <option value="QO">Question à choix ouvert</option>
                        <option value="QM">Question à choix multiple</option>
                        <option value="QC">Question à choix unique</option>  
                    </select>
                    
                    <input type="text" :value="titlequest">
                    
                    <input type="button" value="supprimer">
                    
                    <editopenquestion v-if="typequest === 'QO' " ></editopenquestion>
                    <editclosedquestion v-if ="typequest === 'QM'" :reponse="reponse" ></editclosedquestion>
                    <editclosedquestion v-else-if ="typequest === 'QC'" :reponse="reponse" ></editclosedquestion>
                    <br><br>
               </div>`


};

let editformspage = {
    components:{ editquestion },
    props:{
      title: String,
        tabamodif:Object

    },
    template: `<div>
                    <input type="text" value="title">
                    <input type="text" value="description">
                    <br><br>
                    <editquestion v-if="Object.keys(this.tabamodif).length === 0"></editquestion>
                    <div  v-for="tabamodif in tabamodif" v-else>
                        <editquestion :titlequest="tabamodif.titlequest" :typequest="tabamodif.typequest" :reponse="tabamodif.reponse" ></editquestion>
                    </div>
                    
                    <input type="button" value="nouvelle question" >
                    
                    <input type="button" value="sauver le formulaire">
               </div>`,
    //methods:{
        //save: function(){
        //    this.$parent.$data.newtab = this.$parent.$data.tabamodif
        //},
       // newquest: function(){
       //     this.$emit('ajtquest')
      //  }
        //}
};

let qunique = {
    props:{
        title: String,
        reponse: Object
    },
    template: `<div>
                 <p>{{ title }}</p>
                 <div  v-for="reponse in reponse">
                    <input  type="radio" :id="reponse.id" :name="reponse"><label for="reponse.id">{{ reponse.rep }}</label>
                 </div>
                 <br><br>
             </div>`
};

let qmultiple = {
    props:{
        reponse: Object,
        title: String
    },
    template: `<div>
                 <p>{{ title }}</p>
                 <div v-for="reponse in reponse">
                    <input type="checkbox"><label>{{ reponse.rep }}</label>
                </div>
                <br><br>
             </div>`
};

let qouverte = {
    props:{
        title: String,
        nbmot: Number
    },
    template: `<div>
                 <p>{{ title }}</p>
                 <input type="text" v-for="nbmot in nbmot">
                 <br><br>
             </div>`

};

let subjectpage = {
    components:{ qouverte, qmultiple, qunique },
    props:{
        notreformulaire: Object
    },
    template: `<div>
            <div v-for="notreformulaire in notreformulaire">
                    <qouverte v-if="notreformulaire.typequest ==='QO'" :title="notreformulaire.titlequest" :nbmot="notreformulaire.nbmot"></qouverte>
                    <qmultiple v-if="notreformulaire.typequest ==='QM'" :title="notreformulaire.titlequest" :reponse="notreformulaire.reponse"></qmultiple>
                    <qunique v-if="notreformulaire.typequest ==='QU'" :title="notreformulaire.titlequest" :reponse="notreformulaire.reponse"></qunique>
               </div>
               </div>`

};

new Vue ({
    el: '#app' ,
    components: { navbar, formspage, editformspage, subjectpage },
    data: {
        curentpage: "formulaire",
        formu: "active",
        modif: "",
        upco: "",

        title: "titre d'un formulaire",
        description: "descriptionx formulaire",

        question: {
            0: {
                id: 0,
                title: "Le premier questionnaire",
                description: "la description du premier questionnaire"
            },
            1: {
                id: 1,
                title: "Le second questionnaire",
                description: "la description du second questionnaire"
            },
            2: {
                id: 2,
                title: "Le troisième questionnaire",
                description: "la description du troisième questionnaire"
            }
        },
        idasupprimer: -1,
        tabloadform: {
            0: {
                0: {
                    id: 0,
                    titlequest: "Une première question a choix ouvert charger",
                    typequest: "QO"
                },
                1: {
                    id: 1,
                    titlequest: "Une seconde question a choix multiple charger",
                    typequest: 'QM',
                    reponse: {
                        0: "ceci est une prémière réponse",
                        1: "ceci est une seconde réponse"
                    }
                }
            },
            1: {
                0: {
                    id: 1,
                    titlequest: "Une seconde question a choix multiple charger",
                    typequest: 'QM',
                    reponse: {
                        0: "ceci est une prémière réponse",
                        1: "ceci est une seconde réponse"
                    }

                },
                1: {
                    id: 0,
                    titlequest: "Une première question a choix ouvert charger",
                    typequest: "QO"
                }
            },
            2: {
                0: {
                    id: 1,
                    titlequest: "Une seconde question a choix multiple charger",
                    typequest: 'QM',
                    reponse: {
                        0: "ceci est une prémière réponse",
                        1: "ceci est une seconde réponse"
                    }

                },
                1: {
                    id: 0,
                    titlequest: "Une première question a choix ouvert charger",
                    typequest: "QO"
                },
                2: {
                    id: 1,
                    titlequest: "Une seconde question a choix multiple charger",
                    typequest: 'QM',
                    reponse: {
                        0: "ceci est une prémière réponse",
                        1: "ceci est une seconde réponse"

                    }

                }
            }
            },
            amodif: -1,
            notreformulaire: {
                0:{
                    id:0,
                    titlequest: "Voici une question ouverte",
                    typequest: "QO",
                    nbmot:10

                },
                1:{
                    id:1,
                    titlequest: "Voici une question à choix multiple",
                    typequest: "QM",
                    reponse:{
                        0: { id: 0,
                            rep:"une premiere reponse"},
                        1: { id: 1,
                            rep:"une seconde reponse"},
                    }
                },
                2:{
                    id:2,
                    titlequest: "Voici une seconde question ouverte",
                    typequest: "QO",
                    nbmot:5
                },
                3:{
                    id:3,
                    titlequest: "Voici une question à choix unique",
                    typequest: "QU",
                    reponse:{
                        0: { id: 0,
                            rep:"une premiere reponse"},
                        1: { id: 1,
                            rep:"une seconde reponse"},
                    }
                },
                4:{
                    id:4,
                    titlequest: "Voici une seconde question à choix multiple",
                    typequest: "QM",
                    reponse:{
                        0: { id: 0,
                            rep:"une premiere reponse"},
                        1: { id: 1,
                            rep:"une seconde reponse"},
                    }
                }
            }


        },
        methods: {
            formulaire: function () {
                this.formu = "active";
                    this.modif = "";
                    this.upco = "";
                    this.curentpage = "formulaire"
            },
            modification: function () {
                this.upco = " " ;
                    this.formu = " " ;
                    this.modif = "active";
                    this.curentpage = "modification"
            },
            upcoming: function () {
                this.formu = " ";
                    this.modif = " ";
                    this.upco = "active";
                    this.curentpage = "upcoming"
            },
            suppression: function () {
                delete this.question.idasupprimer;

            },
            modifform: function () {
                var tabamodif= this.tabloadform.amodif;
                this.curentpage = "newform";

                console.log(tabamodif);

                return tabamodif
            }
            ,
            tab: function () {
                console.log(Object.keys(this.tabloadform).length === 0)
            },
            ajtquest: function () {
                this.tabloadform.push({'Object.keys(this.tabloadform).length': {id: Object.keys(this.tabloadform).length}})
            },
            subject: function(){
                this.curentpage = "subject";
            }
        }

})