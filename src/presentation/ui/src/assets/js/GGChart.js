import Chart from 'vue-charts/src/components/chart'

export default Object.assign(Chart, {
  name: 'GGChart',
  watch: {
    options: {
      handler: function (val, oldVal) {
        if (this.wrapper) {
          this.wrapper.setOptions(this.options)
        }
      },
      deep: true
    }
  }
})
