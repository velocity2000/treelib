using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RandomizedBinarySearchTree
{

    class Tree_node
    {
        
        public int info;
        public int size = 1;
        public Tree_node left;
        public Tree_node right;
    }
    class RandomziedBinarySearchTree
    {
        public Tree_node m_root;
        private Random R = new Random();
        private Tree_node LeftSplit;
        private Tree_node RightSplit;
        public void insert(int x)
        {
            insertElem(x, ref m_root);

        }
        private Tree_node insertElem(int x, ref Tree_node T)
        {
            
            int n, r;
            if (T == null)
            {
                n = 0;
            }
            else { n = T.size; }

            r = R.Next(0, n+1);
            if (r == n)
            {
                
                return InsertAtRoot(x, ref T);
            }
            if (x < T.info)
            {
                T.left = insertElem(x, ref  T.left);
            }
            else
            {
                T.right = insertElem(x, ref T.right);
            }
            traverse(m_root);
            return T;

        }


        private Tree_node S = null;
        private Tree_node G = null;
        public Tree_node InsertAtRoot(int x, ref Tree_node T)
        {
            Split(x, T, ref S, ref  G);
            T = new Tree_node();
            T.info = x;
            T.left = S;
            T.right = G;
            traverse(m_root);
            return T;
        }
        public void Split(int x, Tree_node T, ref Tree_node S, ref Tree_node G)
        {
            if (T == null)
            {
                S = G = null;
                return;
            }
            if (x < T.info)
            {
                G = T;
                Split(x, T.left, ref S, ref G.left);
            }
            else
            {
                S = T;
                Split(x, T.right, ref S.right, ref G);
            }





            return;
        }

        private void get_left_most(Tree_node ptr, ref int elem)
        {
            elem = ptr.info;
            Tree_node tmp = ptr.right;
            ptr = tmp;
        }
        private void remove_node(Tree_node node_ptr, int elem)
        {
            //delete node_ptr;
            if (node_ptr.left == null && node_ptr.right == null)
            {

            }
            else
                if (node_ptr.left != null && node_ptr.right == null)
                {
                    Tree_node tmp = node_ptr.left;
                    node_ptr = tmp;
                }
                else
                    if (node_ptr.right != null && node_ptr.left == null)
                    {
                        Tree_node tmp = node_ptr.right;
                        node_ptr = tmp;
                    }
                    else
                    {
                        //          get_left_most(node_ptr.right, node_ptr.info);
                    }

        }
        private void traverse(Tree_node cur)
        {
            if (cur != null)
            {
                int x = 0, y = 0;
                if (cur.left == null) { }
                else x = cur.left.size;
                if (cur.right == null) { }
                else y = cur.right.size;
                cur.size = x + y + 1;
                
                traverse(cur.left);

                traverse(cur.right);


            }

        }
        public void traversePrint(Tree_node cur)
        {
            if (cur != null)
            {
                 traversePrint(cur.left);
                 Console.WriteLine(cur.info);
                traversePrint(cur.right);
            }
        }
        public void print()
        {
            traversePrint(m_root);
        }
        private void private_insert(ref Tree_node node_ptr, int elem)
        {
            if (node_ptr == null)
            {
                node_ptr = new Tree_node();
                node_ptr.info = elem;

                return;
            }
            if (node_ptr.info > elem)
            {
                private_insert(ref node_ptr.left, elem);
            }
            else
            {
                private_insert(ref node_ptr.right, elem);
            }

        }
    }

    class Program
    {







        static void Main(string[] args)
        {
            RandomziedBinarySearchTree T = new RandomziedBinarySearchTree();
            T.insert(5);
            T.insert(3);
            T.insert(14);
            T.insert(1);
            T.insert(12);
            T.insert(7);
            T.insert(3);
            ////T.insert(5);
            ////T.insert(8);
            ////T.insert(4);
            ////T.insert(3);
            ////T.insert(9);
            ////T.insert(12);
            ////T.insert(2);
            ////T.insert(26);
            ////T.insert(5);
            ////T.insert(3);
            ////T.print();
            T.print();
            Console.ReadKey();
        }
    }
}
