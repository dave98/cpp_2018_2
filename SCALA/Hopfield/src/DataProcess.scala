import scala.io.Source

class DataProcess {
  var data_size: Int = 0
  var data_number: Int = 0
  var data_distribution: Int = 0
  var ruta: String = ""
  
  def this(_size: Int, _number: Int, _distribution: Int, _ruta: String) = {
    this();
    this.data_size = _size
    this.data_number = _number
    this.data_distribution = _distribution
    this.ruta = _ruta
    //println("Hopfield Iniciado")
  }
  
  //Array.ofDim[Int](this.data_number, this.data_size)
  def read_data() : Array[Array[Int]] = {
    var answer = Array.ofDim[Int](this.data_number ,this.data_size)   
    val filename = Source.fromFile(this.ruta)
    var i: Int = 0
    var j: Int = 0
    
    for(line <- filename.getLines()){
      for(word <- line){
        if(word == '1' || word == '0'){

          answer(i)(j) = word.toInt - '0'
           if(answer(i)(j) == 0){
             answer(i)(j) = -1    
           }          
          j += 1
        }
        if(j >= this.data_size) {
          j = 0
          i += 1
        }
      }
    }
    filename.close()
    answer
  }
  
  def get_element(_ruta: String, format: Boolean): Array[Int] = {
   var answer = Array.ofDim[Int](this.data_size)
   val filename = Source.fromFile(_ruta)
   var i: Int = 0
   //var line = filename.getLines()
   for(line <- filename.getLines()){
     for(word <- line){
       if(word == '0' || word == '1'){
         answer(i) = word.toInt - '0'
         if(format){
           if(answer(i) == 0){
             answer(i) = -1    
           }
         }
         i += 1
       }
       if(i > this.data_size){
         println("Alerta al recibir dato -  Valores excedidos")
       }
     }
   }
   answer
  }

}