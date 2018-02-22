<template>
	<h1>Le Graph du formulaire numéro</h1>

    <div id="programmatic_dashboard_div">
      <table class="columns">
        <tr>
          <td>
            <div id="programmatic_control_div1" style="padding-left: 2em; min-width: 250px"></div>
            <div id="programmatic_control_div2" style="padding-left: 2em; min-width: 250px"></div>
            <p style="text-align: center">(Rang,Seuil)</p>
          </td>
          <td>
            <div id="programmatic_chart_div"></div>
          </td>
        </tr>
      </table>
    </div>
</template>

<script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <script type="text/javascript">
      google.charts.load('current', {'packages':['corechart', 'controls']});
      google.charts.setOnLoadCallback(drawStuff);

      function drawStuff() {

        var dashboard = new google.visualization.Dashboard(
          document.getElementById('programmatic_dashboard_div'));

        // We omit "var" so that programmaticSlider is visible to changeRange.
        var programmaticSlider1 = new google.visualization.ControlWrapper({
          'controlType': 'NumberRangeFilter',
          'containerId': 'programmatic_control_div1',
          'options': {
            'filterColumnLabel': 'Rang',
            'ui': {'labelStacking': 'vertical'}
          }
        });

        var programmaticSlider2 = new google.visualization.ControlWrapper({
          'controlType': 'NumberRangeFilter',
          'containerId': 'programmatic_control_div2',
          'options': {
            'filterColumnLabel': 'Seuil',
            'ui': {'labelStacking': 'vertical'}
          }
        });


        var programmaticChart  = new google.visualization.ChartWrapper({
          'chartType': 'ScatterChart',
          'containerId': 'programmatic_chart_div',
          'options': {
            'width': 600,
            'height': 600,
            'legend': 'none',
            'chartArea': {'left': 20, 'top': 15, 'right': 0, 'bottom': 20},
            'pieSliceText': 'value',
            'crosshair': { trigger: 'both', color: 'red'  },
            'vAxis': {
              title: 'Seuil'
          },
            'hAxis': {
              title: 'Rang'
            }
          }
        });

        var data = new google.visualization.DataTable();
        data.addColumn('number','Rang');
        data.addColumn('number', 'Seuil');
        data.addColumn( { type: 'string', role: 'annotation' });
        dashboard.bind(programmaticSlider1, programmaticChart);
        dashboard.bind(programmaticSlider2, programmaticChart);
        dashboard.draw(data);
        for (var i = 0; i < 100; i++)
          data.addRow([Math.floor(Math.random()*100),Math.floor(Math.random()*100),"mot "+i]);
      }

    </script>