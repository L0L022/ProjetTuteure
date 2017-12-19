
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
        id: Number
    },
    template:`<div>
                <p>{{id}}</p>
                <p>{{ title }}</p>
                
                <p>
                {{ description }} 
                <input type="button" name="supression" value="supression" >
                <input type="button" name="modifcation" value="modifcation">
                <input type="button" name="reponse" value="reponse"><br/><br/>
                
                </p>
</div>`
};

let formspage = {
    props: {question: Object },
    components: { shortformspage },
    template: `<div>
                <div v-for="question in question">
                    <shortformspage :title="question.title" :description="question.description" :id="question.id" ></shortformspage>
                </div>
                <input type="button" name="new" value="nouveau formulaire">
</div>`
};

new Vue ({
    el: '#app' ,
    components: { navbar, formspage },
    data: {
        curentpage: "formulaire",
        formu: "active",
        modif: "",
        upco: "",

        title: "titre d'un formulaire",
        description: "descriptionx formulaire",

        question:{
            "0":{
                id: 0,
                title: "Le premier questionnaire",
                description: "la description du premier questionnaire"
            },
            1:{
                id: 1,
                title: "Le second questionnaire",
                description: "la description du second questionnaire"
            },
            "2":{
                id: 2,
                title: "Le troisième questionnaire",
                description: "la description du troisième questionnaire"
            }
        }
    },
    methods: {
        formulaire(){
            this.formu="active",
            this.modif="",
            this.upco="",
            this.curentpage="formulaire"
        },
        modification(){
            this.upco = " " ,
            this.formu = " " ,
            this.modif = "active"
            this.curentpage="modification"
        },
        upcoming(){
            this.formu=" ",
            this.modif=" ",
            this.upco="active",
            this.curentpage="upcoming"
        }
    }
})