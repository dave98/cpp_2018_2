

class Hopfield(var data: Array[Array[Float]] = Array.ofDim[Float](0,0), 
               var f_data: Array[Array[Float]] = Array.ofDim[Float](0,0), 
               var cant_data: Int = 0,
               var data_size: Int = 0,
               var data_distribution: Int = 0,
               var max_iter: Int = 0) extends SomeFunctions{
  
  def this(_d_size: Int, _cant_data: Int, _d_distribution: Int, _max_iter : Int){
    this();
    this.data_size = _d_size
    this.data_distribution = _d_distribution
    this.max_iter = _max_iter
    this.cant_data = _cant_data;
    this.data = Array.ofDim[Float](this.cant_data, this.data_size)
    this.f_data = Array.ofDim[Float](this.data_size, this.data_size)
    println("Used Secondary Constructor")
  }
  
  def set_data_element(i_mat: Array[Int]) = {
    //Nativization Process
    var nav: Array[Array[Float]] = this.vector_to_matrix(i_mat)
    var nav_t: Array[Array[Float]] = this.get_matrix_transpose(nav)

    var result: Array[Array[Float]] = this.matrix_multiplication(nav_t, nav)
    this.add_to_data(result)
  }

  def add_to_data(mat: Array[Array[Float]]) = {
    if( (mat.length != this.f_data.length) || (mat(0).length != this.f_data(0).length) ){
      println("Error: Add to data")
    }
    
    for(i <- 0 until mat.length){
      for(j <- 0 until mat(0).length){
        this.f_data(i)(j) += mat(i)(j)
      }
    }
  }
  
  def recognize(i_mat: Array[Int]) = {
    println("Iniciando Reconocimiento")
    var nav: Array[Array[Float]] = this.vector_to_matrix(i_mat)

     for(i <- 0 until this.f_data.length){
       this.f_data(i)(i) = 0
     } 
     
    //println("Weigths")
    //this.print_matrix(this.f_data)
     this.recognize_dev(nav, 0, 0)
  }
  
  def recognize_dev(i_mat: Array[Array[Float]], current_iter: Int, energia: Float): Unit = {
    //println("Iteraccion " + current_iter)
    if(current_iter < this.max_iter){
      var r_matrix: Array[Array[Float]] = this.matrix_multiplication(i_mat, this.f_data)
      var inner_energia : Float = this.get_energia(i_mat)
      this.funcion_reconocimiento(r_matrix)
      
      /*println("Patron ")
      this.print_matrix(i_mat)
      
      println("Weigths")
      this.print_matrix(this.f_data)

      println("Results")
      this.print_matrix(r_matrix)*/
      
      if((this.matrix_equal(i_mat, r_matrix)) && (energia == inner_energia) ){
        println("Resultado Final tras " + current_iter + " iteracciones") 
        //this.print_matrix(r_matrix)
        this.print_ascii(r_matrix)
      }
      else{
        this.recognize_dev(r_matrix, current_iter + 1, inner_energia)
      }
    }
  }
  
  def get_energia(i_mat:Array[Array[Float]]) : Float = {
    var answer: Float = 0;
    for(i <- 0 until this.f_data.length){
      for(j <- 0 until this.f_data(0).length){
        answer += (this.f_data(i)(j) + i_mat(0)(i) + i_mat(0)(j))
      }
    }
    answer
  }
  
  //Be careful with parameters 0 and -1
  def funcion_reconocimiento(i_mat: Array[Array[Float]]) = {
    for(i <- 0 until i_mat.length){
      for(j <- 0 until i_mat(0).length){
        if(i_mat(i)(j) >= 0){
          i_mat(i)(j) = 1
        }
        else{
          i_mat(i)(j) = -1
        }
      }
    }
  }
  
}