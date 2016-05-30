extern crate rand;
extern crate time;

use std::error::Error;
use std::fs::File;
use std::io::prelude::*;
use std::path::Path;
use std::io;
use rand::Rng;
use time::PreciseTime;

#[derive(Debug, Clone, Copy)]
struct Edge
{
	dWeight: i32,
	iVert1: usize,
	iVert2: usize,
}

impl Edge
{
	fn new(w: i32, v1: usize, v2: usize) -> Edge
	{
		Edge
		{
			dWeight: w,
			iVert1: v1,
			iVert2: v2,
		}
	}

	fn equals(&self, rhs: &Edge) -> bool
	{
		self.dWeight == rhs.dWeight &&
		((self.iVert1 == rhs.iVert1 &&
		self.iVert2 == rhs.iVert2) ||
		(self.iVert1 == rhs.iVert2 &&
		self.iVert2 == rhs.iVert1))
	}
}

fn VectorContainsEdge(vector: &Vec<Edge>, edge: &Edge) -> bool
{
	for i in 0..vector.len()
	{
		if edge.equals(&vector[i])
		{
			return true;
		}
	}

	false
}

fn VectorContainsUSIZE(vector: &Vec<usize>, val: &usize) -> bool
{
	for i in 0..vector.len()
	{
		if vector[i] == *val
		{
			return true;
		}
	}

	false
}

struct Graph
{
	aadMatrix: Vec<Vec<i32>>,
	aadResult: Vec<Vec<i32>>,
}

impl Graph
{
	fn new(n: usize) -> Graph
	{
		Graph
		{
			aadMatrix: vec![vec![0;n];n],
			aadResult: vec![vec![0;n];n],
		}
	}

	fn create_graph(&mut self, nedges: usize, minw: i32, maxw: i32)
	{
		let mut edges_count: usize = 0;
		if nedges > ((self.aadMatrix.len()) * (self.aadMatrix.len() - 1) / 2)
		{
			edges_count = (self.aadMatrix.len()) * (self.aadMatrix.len() - 1) / 2;
			println!("Impossible to create this graph. Edges count set to: {}",
				edges_count);
		}
		else 
		{
			edges_count = nedges;
		}

		let mut weight = 0;
		for i in 0..self.aadMatrix.len()-1
		{
			match edges_count
			{
				0 => break,
				_ => edges_count -= 1,
			}

			weight = rand::thread_rng().gen_range(minw, maxw);

			self.aadMatrix[i][i+1] = weight;
			self.aadMatrix[i+1][i] = weight;
		}

		while edges_count != 0
		{
			let v1 = rand::thread_rng().gen_range(0, self.aadMatrix.len()-1);
			let v2 = rand::thread_rng().gen_range(0, self.aadMatrix.len()-1);

			if v1 != v2 &&
				self.aadMatrix[v1 as usize][v2 as usize] == 0
			{
				weight = rand::thread_rng().gen_range(minw, maxw);
				self.aadMatrix[v1 as usize][v2 as usize] = weight;
				self.aadMatrix[v2 as usize][v1 as usize] = weight;

				match edges_count 
				{
					0 => break,
					_ => edges_count -= 2,
				}
			}
		}
	}

	fn kruskal_algo(&mut self)
	{
		let mut components = vec![0; self.aadMatrix.len()];
		let mut astEdges = vec![Edge::new(0,0,0);0];

		for i in 0..components.len()
		{
			components[i] =  i;
		}

		for i in 0..self.aadMatrix.len()
		{
			for j in i+1..self.aadMatrix[i].len()
			{
				let edge = Edge::new(self.aadMatrix[i][j], i, j);
				astEdges.push(edge);
			}
		}

		astEdges.sort_by(|a: &Edge, b: &Edge|
		{
			a.dWeight.cmp(&b.dWeight)
		});

		for edge in astEdges
		{
			let mut a = components[edge.iVert1];
			let mut b = components[edge.iVert2];
            if a != b
            {
            	for i in 0..components.len()
            	{
            		if components[i] == b
            		{
            			components[i] = a;
            		}
            	}

            	self.aadResult[edge.iVert1][edge.iVert2] = edge.dWeight;
            	self.aadResult[edge.iVert2][edge.iVert1] = edge.dWeight;
            }
		}
	}

	fn boruvka_algo(&mut self)
	{
		let mut components = vec![0; self.aadMatrix.len()];
		for i in 0..components.len()
		{
			components[i] = i;
		}

		let mut astEdges = vec![Edge::new(0,0,0);0];
		let mut astResult = vec![Edge::new(0,0,0);0];
		let mut adContains = vec![0;0];
		let mut stEdge = Edge::new(0,0,0);

		while astResult.len() < self.aadMatrix.len()-1
		{
			astEdges = vec![Edge::new(0,0,0);0];
			adContains = vec![0;0];

			for i in 0..self.aadMatrix.len()
			{
				if !VectorContainsUSIZE(&adContains, &components[i])
				{
					adContains.push(components[i]);
					for j in 0..self.aadMatrix.len()
					{
						if components[i] == components[j]
						{
							stEdge = Edge::new(999999,999999,999999);
							for k in 0..self.aadMatrix.len()
							{
								if ( !VectorContainsEdge(&astResult, &stEdge) &&
									(components[i] != components[k]) &&
									(self.aadMatrix[j][k] < stEdge.dWeight) &&
									(self.aadMatrix[j][k] > 0) )
								{
									stEdge = Edge::new(self.aadMatrix[j][k], j, k);
								}
							}
						}
					}
					astEdges.push(stEdge);
				}
			}
			for i in 0..self.aadMatrix.len()
			{
				for edg in &astEdges
				{
					if edg.iVert1 == i
					{
						components[edg.iVert2] == components[i];
					}
					if edg.iVert2 == i
					{
						components[edg.iVert1] == components[i];
					}
				}
			}

			for edg in &astEdges
			{
				astResult.push(*edg);
			}
		}
	}
}

fn main()
{
	let path = Path::new("result.csv");
	let display = path.display();

	let mut file = match File::create(&path) {
        // The `description` method of `io::Error` returns a string that
        // describes the error
        Err(why) => panic!("couldn't open {}: {}", display,
                                                   why.description()),
        Ok(file) => file,
    };

	let mut n_vertex = 101;
	let m_mult = 1000;

	file.write_all(("n;m;kruskal;boruvka;\n").as_bytes());

	loop
	{
		let mut graph = Graph::new(n_vertex);
		print!("Generating graph with {} vertexes and {} edges...\n", n_vertex,
			n_vertex * m_mult);
		graph.create_graph(n_vertex * m_mult, 0, 40000);
		print!("\t\t\tDone.\n");

		print!("Kruskal started...");
		let start = PreciseTime::now();
		graph.kruskal_algo();
		let end = PreciseTime::now();
		print!("\t\t\t\tDone in {} ms\n\n",
				start.to(end).num_milliseconds());
		let kruskal_time = start.to(end).num_milliseconds();

		print!("Boruvka started...");
		let start = PreciseTime::now();
		graph.boruvka_algo();
		let end = PreciseTime::now();
		print!("\t\t\t\tDone in {} ms\n\n",
				start.to(end).num_milliseconds());
		let boruvka_time = start.to(end).num_milliseconds();

		let string = format!("{};{};{};{};\n", n_vertex, n_vertex * m_mult,
			kruskal_time, boruvka_time);
		file.write_all(string.as_bytes());

		n_vertex += 100;

		if n_vertex > 10001
		{
			break;
		}
	}
}
