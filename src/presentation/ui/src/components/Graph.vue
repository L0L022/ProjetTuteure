<template>
<div class="Graph">
  <el-row>
    <el-col :span="1">
      <el-slider
        v-model="rangeVAxis"
        range
        vertical
        show-stops
        height="500px"
        :min="0"
        :max="100">
      </el-slider>
    </el-col>
    <el-col :span="23">
      <GGChart :chart-type="'ScatterChart'" :columns="columns" :rows="rows" :options="options"></GGChart>
    </el-col>
  </el-row>
  <el-row>
    <el-col :span="24">
      <el-slider
        v-model="rangeHAxis"
        range
        show-stops
        :min="0"
        :max="10">
      </el-slider>
    </el-col>
  </el-row>
</div>
</template>

<script>
import GGChart from '@/assets/js/GGChart'

export default {
  name: 'Graph',
  data: function () {
    return {
      columns: [{
        'type': 'number',
        'label': 'Rang'
      }, {
        'type': 'number',
        'label': 'Seuil'
      }],
      rows: [
        [4, 10],
        [6, 20],
        [2, 60],
        [10, 90]
      ],
      options: {
        title: 'Graphe simple',
        hAxis: {
          title: 'Rang',
          viewWindow: {
            min: 0,
            max: 10
          }
        },
        vAxis: {
          title: 'Seuil',
          viewWindow: {
            min: 0,
            max: 10
          }
        },
        height: 500,
        legend: 'none'
      },
      rangeHAxis: [0, 10],
      rangeVAxis: [0, 100]
    }
  },
  watch: {
    rangeHAxis: function () {
      this.options.hAxis.viewWindow.min = this.rangeHAxis[0]
      this.options.hAxis.viewWindow.max = this.rangeHAxis[1]
    },
    rangeVAxis: function () {
      this.options.vAxis.viewWindow.min = this.rangeVAxis[0]
      this.options.vAxis.viewWindow.max = this.rangeVAxis[1]
    }
  },
  components: {
    GGChart
  }
}
</script>
