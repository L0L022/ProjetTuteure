<template>
<div>
<vue-chart
            :chart-type="chartType"
            :columns="columns"
            :rows="rows"
            :options="options"
        ></vue-chart>
       <div class="block">
    <el-slider v-model="value9" range="" show-stops >
    </el-slider>
  </div>
</div>
</template>

<script>
export default {
  name: 'ListForm',
  props: {
    services: {
      type: Object,
      required: true
    }
  },
        data: function () {
            return {
                columns: [{
                    'type': 'number',
                    'label': 'Element'
                }, {
                    'type': 'number',
                }, {
                    'type': 'string',
                    'role': 'annotation'
                }],

                chartType:'ScatterChart',


                rows: [
                    [8, 1, "dent: 0.05"],
                    [8, 8, "dent: 0.02"]
                ],

                options: {
                    title: 'Company Performance',
                    hAxis: {
                        title: 'Year',
                        minValue: 0,
                        maxValue: 10
                    },
                    vAxis: {
                        title: '',
                        minValue: 0,
                        maxValue: 10
                    },
                    width: 500,
                    height: 500,
                    curveType: 'function'
                },
                 value9: [4, 8],
                rangeVAxis: [0, 8]
            }
        },
  created: function () {
    this.refresh()
  },
  watch: {
  rangeHAxis: function(newV, oldV) {
    this.options.hAxis.minValue = this.rangeHAxis[0]
        this.options.hAxis.maxValue = this.rangeHAxis[1]
  }
  }
}
</script>

<style>
    .block{
        margin-left: 20%;
        margin-right: 20%
    }
</style>