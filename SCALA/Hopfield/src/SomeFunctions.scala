

class SomeFunctions {
  def print_vector(i_vect: Array[Int]) = {
    for(i <- 0 until i_vect.length){
      print(i_vect(i) + " ")
    }
    println()
  }
  
   def print_matrix(mat: Array[Array[Int]]){
    for(i <- 0 until mat.length){
      for(j <- 0 until mat(i).length){
        print(mat(i)(j) + " ") 
      }
      println()
    }
  }
   
  def print_matrix(mat: Array[Array[Float]]){
    for(i <- 0 until mat.length){
      for(j <- 0 until mat(i).length){
        print(mat(i)(j) + " ") 
      }
      println()
    }
  }
   
  def vector_to_matrix(mat: Array[Int]) : Array[Array[Float]] = {
    var answer = Array.ofDim[Float](1, mat.length)
    for(j <- 0 until mat.length){
      answer(0)(j) = mat(j).toFloat
    }
    answer
  }
  
  def get_matrix_transpose(mat: Array[Array[Float]]): Array[Array[Float]] = {
    var answer = Array.ofDim[Float](mat(0).length, mat.length) // mat.length is y and mat(0).length is x
    
    for(i <- 0 until mat.length){
      for(j <- 0 until mat(0).length){
        answer(j)(i) = mat(i)(j)
      }
    }
    answer
  }
  
  def matrix_multiplication(mat_a: Array[Array[Float]], mat_b: Array[Array[Float]] ) : Array[Array[Float]] = {
    var answer = Array.ofDim[Float](mat_a.length, mat_b(0).length)
    
    if(mat_a(0).length != mat_b.length){
      println("Error: Indices fuera de orden en la multiplicacion")
    }
    
    for(i <- 0 until mat_a.length){
      for(j <- 0 until mat_b(0).length){
        for(k <- 0 until mat_a(0).length){
          answer(i)(j) += mat_a(i)(k) * mat_b(k)(j)    
        }
      }
    }
    answer
  }
  
  //I'll assume they're dimensional equally matrices
  def matrix_equal(m_a: Array[Array[Float]], m_b: Array[Array[Float]]) : Boolean = {
    var answer: Boolean = true
    for(i <- 0 until m_a.length){
      for(j <- 0 until m_a(0).length){
        if(m_a(i)(j) != m_b(i)(j)){
          answer = false
        }
      }
    }
    answer
  }
  
  def print_ascii(i_mat: Array[Array[Float]]) = {
    var flag: Int = 164
    for(i <- 0 until i_mat.length){
      for(j <- 0 until i_mat(0).length){
        if(i_mat(i)(j) == 1.0){
          print(flag.toChar)  
          print(" ")
        }
        else{
          print("  ")
        }
      }
    }
  }
  
}