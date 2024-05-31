    // Функция для рисования розы Гранди
    let drawRose = (speed, effect) => {
        // Размеры SVG
        let width = 500;
        let height = 500;
        
  
        // Создаем SVG элемент
        let svg = d3.select("#flower-container")
          .attr("width", width)
          .attr("height", height);
  
        // Функция для перевода полярных координат в декартовы
        let polarToDecart = (r, phi) => {
          let x = r * Math.cos(phi);
          let y = r * Math.sin(phi);
          return [x, y];
        }
  
        // Задаем параметры розы
        let n = 5; // Количество лепестков
        let r = 150; // Радиус
  
        // Строим розу
        let points = [];
        for (let phi = 0; phi <=  Math.PI; phi += 0.01) {
          let radius = r * Math.sin(n * phi);
          let [x, y] = polarToDecart(radius, phi);
          points.push([x, y]);
        }
  
        // Создаем линию из точек
        let line = d3.line()
          .curve(d3.curveBasisClosed);
  
        // Создаем объект d3.path для рисования пути
        let path = line(points);
  
        // Создаем группу для розы
        let roseGroup = svg.append("g")
          .attr("transform", `translate(${width / 2}, ${height / 2})`);
  
        // Добавляем путь розы
        let pathElement = roseGroup.append("path")
          .attr("fill", "none")
          .attr("stroke", "blue")
          .attr("stroke-width", 2)
          .attr("d", path);
  
        // Добавляем смайлик
        let smile = roseGroup.append("g")
          .style("stroke", "brown")
          .style("stroke-width", 2)
          .style("fill", "brown");
  
        //лицо
        smile.append("circle")
          .attr("cx", 0)
          .attr("cy", 0)
          .attr("r", 12)
          .style("fill", "yellow");
  
        //левый глаз
        smile.append("circle")
          .attr("cx", -4)
          .attr("cy", -2)
          .attr("r", 1);
  
        //правый глаз
        smile.append("circle")
          .attr("cx", 4)
          .attr("cy", -2)
          .attr("r", 1);
  
        // улыбка
        let arc = d3.arc()
          .innerRadius(7)
          .outerRadius(7);
        // Ушки
        smile.append("path")
        .attr("d", "M-10,-3 L-14,-13 L-5,-11 Z")
        .style("fill", "brown");
        smile.append("path")
        .attr("d", "M10,-5 L13,-10 L7,-10 Z")
        .style("fill", "brown");

        // Носик
        smile.append("path")
        .attr("d", "M0,5 L0,8 L2,6 L-2,6 Z")
        .style("fill", "brown");
  
        smile.append("path")
          .attr("d", arc({startAngle: Math.PI /3 * 2, endAngle: Math.PI/3 * 4}))
          .style("stroke", "brown");
  
        // Получаем общую длину пути
        let pathLength = pathElement.node().getTotalLength();
  
        // Анимируем движение смайлика по пути
        let smileTransition = smile
          .attr("transform", `translate(${points[0][0]},${points[0][1]})`)
          .transition()
          .ease(d3.easeLinear)
          .duration(speed) // Длительность анимации в миллисекундах
          .attrTween("transform", function() {
            return function(t) {
              let pos = pathElement.node().getPointAtLength(pathLength * t);
              return `translate(${pos.x},${pos.y})`;
            }
          })
          .on("end", function() {
            d3.select(this).transition().attr("transform", `translate(${points[0][0]},${points[0][1]})`);
          });
  
        // Добавляем эффект увеличения, если выбран соответствующий вариант
        if (effect === "scaling") {
          applyScalingEffect();
  
        }
        if (effect === "rotation") {
          applyRotationEffect();
        }
      }
  
      function applyScalingEffect() {
        let flowerContainer = d3.select("#flower-container");
  
        flowerContainer.transition()
            .duration(4500)
            .attrTween("transform", function() {
                return d3.interpolateString("scale(1)", "scale(1.5)");
            })
            .transition()
            .duration(4500)
            .attrTween("transform", function() {
                return d3.interpolateString("scale(1.5)", "scale(1)");
            })
            .on("end", function repeat() {
                d3.active(this)
                    .attrTween("transform", function() {
                        return d3.interpolateString("scale(1)", "scale(1.5)");
                    })
                    .transition()
                    .duration(4500)
                    .attrTween("transform", function() {
                        return d3.interpolateString("scale(1.5)", "scale(1)");
                    })
                    .transition()
                    .on("end", repeat);
            });
      }
  
      // Функция для применения эффекта вращения
      function applyRotationEffect() {
        let flowerContainer = d3.select("#flower-container");
        flowerContainer.transition()
            .duration(4500)
            .attrTween("transform", function() {
                return d3.interpolateString("rotate(0)", "rotate(360)");
            });
      }
  
      // Функция для запуска анимации
      function startAnimation() {
        let speed = parseInt(document.getElementById("speed").value);
        let effect = document.getElementById("effect").value;
        drawRose(speed, effect);
      }
  
      // Функция для очистки анимации
      function clearAnimation() {
        d3.select("#flower-container").selectAll("*").remove();
      }