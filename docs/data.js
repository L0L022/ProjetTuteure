var form = {
    "id": 0,
    "name": "",
    "description": ""
};

var question = {
    "id": 0,
    "form": 0,
    "title": "",
    "type": ""
};

var choice = {
    "id": 0,
    "question": 0,
    "label": ""
};

var subject = {
    "id": 0,
    "isValid": false
};

var answer = {
    "id": 0,
    "subject": 0,
    "question": 0
};

// getForm

var form = {
  "id": 0,
  "name": "",
  "description": "",
  "questions": {
    "0": {
      "id": 0,
      "title": "",
      "type": "opened",
      "nbAnswers": 10
    },
    "1": {
      "id": 1,
      "title": "",
      "type": "unique",
      "choices": {
        "0": {
          "id": 0,
          "label": ""
        },
        "1": {
          "id": 1,
          "label": ""
        },
        "2": {
          "id": 2,
          "label": ""
        }
      }
    },
    "2": {
      "id": 2,
      "title": "",
      "type": "multiple",
      "choices": {
        "0": {
          "id": 0,
          "label": ""
        },
        "1": {
          "id": 1,
          "label": ""
        },
        "2": {
          "id": 2,
          "label": ""
        }
      }
    }
  }
};

var form = {
  "id": 0,
  "name": "Étude de l'IUT d'Arles",
  "description": "info2 - décembre 2018",
  "questions": {
    "0": {
      "id": 0,
      "title": "Que pensez-vous quand je vous dis IUT ?",
      "type": "opened",
      "nbAnswers": 10
    },
    "1": {
      "id": 1,
      "title": "Votre matière préférée",
      "type": "unique",
      "choices": {
        "0": {
          "id": 0,
          "label": "Anglais"
        },
        "1": {
          "id": 1,
          "label": "Algo avancé"
        },
        "2": {
          "id": 2,
          "label": "Mathématiques"
        }
      }
    },
    "2": {
      "id": 2,
      "title": "Vos langages préférés",
      "type": "multiple",
      "choices": {
        "0": {
          "id": 0,
          "label": "C++"
        },
        "1": {
          "id": 1,
          "label": "PHP"
        },
        "2": {
          "id": 2,
          "label": "BASH"
        }
      }
    }
  }
};

var subject = {
  "id": 0,
  "isValid": false,
  "answers": {
    "0": {
      "id": 0,
      "words": ""
    },
    "1": {
      "id": 1,
      "choice": 0
    },
    "2": {
      "id": 2,
      "choices": []
    }
  }
};

var subject = {
  "id": 0,
  "isValid": false,
  "answers": {
    "0": {
      "id": 0,
      "words": "une liste de  mots, il va faloir modifier la bdd"
    },
    "1": {
      "id": 1,
      "choice": 2
    },
    "2": {
      "id": 2,
      "choices": [
        0,
        2
      ]
    }
  }
};


var form = {
  id: 0,
  name: "Étude de l'IUT d'Arles",
  description: "info2 - décembre 2018",
  questions: {
    0: {
      id: 0,
      title: "Que pensez-vous quand je vous dis IUT ?",
      type: "opened",
      nbAnswers: 10
    },
    1: {
      id: 1,
      title: "Votre matière préférée",
      type: "unique",
      choices: {
        0: {
          id: 0,
          label: "Anglais"
        },
        1: {
          id: 1,
          label: "Algo avancé"
        },
        2: {
          id: 2,
          label: "Mathématiques"
        }
      }
    },
    2: {
      id: 2,
      title: "Vos langages préférés",
      type: "multiple",
      choices: {
        0: {
          id: 0,
          label: "C++"
        },
        1: {
          id: 1,
          label: "PHP"
        },
        2: {
          id: 2,
          label: "BASH"
        }
      }
    }
  }
};
