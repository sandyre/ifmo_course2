use std::io;
use std::num;
use std::cmp;

#[derive(Debug, Clone, Copy)]
struct Edge
{
	iVert1: usize,
	iVert2: usize,
}

impl Edge
{
	fn new(v1: usize, v2: usize) -> Edge
	{
		Edge
		{
			iVert1: v1,
			iVert2: v2,
		}
	}

	fn equals(&self, rhs: &Edge) -> bool
	{
		self.iVert1 == rhs.iVert1 &&
		self.iVert2 == rhs.iVert2
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

struct Graph
{
	aadMatrix: Vec<Vec<i32>>,
	aadStream: Vec<Vec<i32>>,
	aabVisited: Vec<bool>,
}

impl Graph
{
	fn new(n: usize) -> Graph
	{
		Graph
		{
			aadMatrix: vec![vec![0;n];n],
			aadStream: vec![vec![0;n];n],
			aabVisited: vec![false;n],
		}
	}

	fn reset_visitance(&mut self)
	{
		self.aabVisited = vec![false;self.aabVisited.len()];
	}

	fn min_cut_vertex(&mut self) -> Vec<i32>
	{
		let mut cut: Vec<i32> = vec![0;1];
		let mut i: i32 = -1;
		while i != (cut.len() - 1) as i32
		{
			i += 1;
			let v = cut[i as usize];
			for j in 0..self.aadMatrix.len()
			{
				if self.aadMatrix[v as usize][j] > 0 &&
					!VectorContainsI32(&cut, j as i32) &&
					(self.aadMatrix[v as usize][j] - self.aadStream[v as usize][j]) != 0
				{
					cut.push(j as i32);
				}
			}
		}

		cut
	}

	fn min_cut(&mut self) -> Vec<Edge>
	{
		let mut cut = self.min_cut_vertex();
		let mut ecut = vec![Edge::new(0,0);0];

		for v in &cut
		{
			for i in 0..self.aadMatrix.len()
			{
				if self.aadMatrix[*v as usize][i] != 0 &&
					!VectorContainsI32(&cut, i as i32)
				{
					ecut.push(Edge::new(*v as usize, i as usize))
				}
			}
		}

		ecut
	}

	fn dfs_ford(&mut self, u: i32, CMin: i32) -> i32
	{		
		self.aabVisited[u as usize] = true;

		if u == (self.aadMatrix.len() - 1) as i32
		{
			return CMin;
		}


		for i in 0..self.aadMatrix.len()
		{
			if self.aadMatrix[u as usize][i] != 0
			{
				if !self.aabVisited[i] 
					&& (self.aadStream[u as usize][i] < self.aadMatrix[u as usize][i])
				{
					let cm: i32 = cmp::min(CMin, (self.aadMatrix[u as usize][i] - self.aadStream[u as usize][i]));
					let delta = Graph::dfs_ford(self, i as i32, cm);
					if delta > 0
					{
						self.aadStream[u as usize][i] += delta;
						self.aadStream[i][u as usize] -= delta;
						return delta;
					}
				}
			}
		}
		
		return 0;
	}

	fn make_oriented(&mut self, source: i32, drain: i32) -> bool
	{
		if (source < self.aadMatrix.len() as i32) &&
			(drain < self.aadMatrix.len() as i32)
		{
			for i in 0..self.aadMatrix.len()
			{
				self.aadMatrix[i][source as usize] = 0;
				self.aadMatrix[drain as usize][i] = 0;
			}
			return false;
		}
		true
	}

	fn print_graph(&mut self)
	{
		for i in 0..self.aadMatrix.len()
		{
			for j in 0..self.aadMatrix.len()
			{
				if self.aadMatrix[i][j] != 0
				{
					println!("Edge from {} to {} with weight: {} stream: {}", 
						i, j, self.aadMatrix[i][j], self.aadStream[i][j]);
				}
			}
		}
	}

	fn print_cut(&mut self)
	{
		let mut cut = self.min_cut();
		for edg in &cut
		{
			println!("Edge from {} to {}", edg.iVert1, edg.iVert2);
		}
	}
}

fn VectorContainsI32(vector: &Vec<i32>, val: i32) -> bool
{
	for i in 0..vector.len()
	{
		if vector[i] == val
		{
			return true;
		}
	}

	false
}

fn main()
{
	let mut graph = Graph::new(6);

	/*
		A = 0
		B = 1
		C = 2
		D = 3
		E = 4
		F = 5
	*/
	graph.aadMatrix[0][1] = 20;
	graph.aadMatrix[1][0] = 20;
	graph.aadMatrix[1][2] = 10;
	graph.aadMatrix[2][1] = -10;
	graph.aadMatrix[1][3] = 15;
	graph.aadMatrix[3][1] = 15;
	graph.aadMatrix[2][4] = 8;
	graph.aadMatrix[4][2] = 8;
	graph.aadMatrix[4][3] = 5;
	graph.aadMatrix[3][4] = -5;
	graph.aadMatrix[4][5] = 9;
	graph.aadMatrix[5][4] = 9;
	graph.aadMatrix[3][5] = 11;
	graph.aadMatrix[5][3] = 11;

    graph.make_oriented(0, 5);

    let mut d = 999999;
    while d > 0
    {
    	graph.reset_visitance();
    	d = graph.dfs_ford(0, 999999);
    }

    println!("Граф:");
    graph.print_graph();

    println!("Минимальный разрез:");
    graph.print_cut();

    println!("Поток через минимальный разрез:");
    let mut f = 0;
    let mut edgs = graph.min_cut();

    for edg in &edgs
    {
    	f += graph.aadStream[edg.iVert1][edg.iVert2];
    }
    println!("{}", f);

    println!("Максимальный поток:");
    f = 0;
    for i in 0..graph.aadMatrix.len()
    {
    	if graph.aadStream[0][i] != 0
    	{
    		f += graph.aadStream[f as usize][i];
    	}
    }
    println!("{}", f);
}