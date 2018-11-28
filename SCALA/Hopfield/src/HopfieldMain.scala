
object HopfieldMain {
  def main(args: Array[String]){
    println(" -- Iniciando Hopfield -- ")
    var D_SIZE: Int = 9
    var D_CANT: Int = 2
    var D_DISTRIBUTION: Int = 3
    var RUTA: String = "data22.txt"
    var RUTA_EXAMPLE: String = "example2.txt"
    var C_ITER: Int = 50
    
    val lector = new DataProcess(D_SIZE, D_CANT, D_DISTRIBUTION, RUTA)
    val a_red = new Hopfield(D_SIZE, D_CANT, D_DISTRIBUTION, C_ITER)
    
    var temp_mat = Array.ofDim[Int](D_CANT, D_SIZE);   
    var example_mat = Array.ofDim[Int](D_SIZE);
    
    
    
    temp_mat = lector.read_data()//Recoge todos los datos
    example_mat = lector.get_element(RUTA_EXAMPLE, true)//Lee la muestra a comparar
    
//164
    
    //a_red.print_vector(example_mat)
    
    println("Received Data")
    for(i <- 0 until temp_mat.length){
      a_red.set_data_element(temp_mat(i))
      a_red.print_ascii(a_red.vector_to_matrix(temp_mat(i)))
      println()
    }
    
    println("Valor a reconocer")
    a_red.print_ascii(a_red.vector_to_matrix(example_mat))
    println()
    
    a_red.recognize(example_mat)
  }
  // Matrix works as references  
  //Some Functions
}