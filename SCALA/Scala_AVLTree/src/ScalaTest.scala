object ScalaTest {
    def main(args: Array[String]){
      val tree = new AVLTree[Int]()
      
      tree.insert(3)
      tree.insert(1)
      tree.insert(2)
    
      println("Arbol completado")
    }
  }