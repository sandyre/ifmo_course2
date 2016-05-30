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
			for j in 0..(f64::sqrt((self.aadMatrix.len()) as f64)) as usize
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
			for i in 0..(f64::sqrt((self.aadMatrix.len()) as f64)) as usize
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
		if u == (f64::sqrt((self.aadMatrix.len() - 1) as f64)) as i32
		{
			return CMin;
		}
		
		self.aabVisited[u as usize] = true;

		for i in 0..(f64::sqrt(self.aadMatrix.len() as f64)) as usize
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
		0
	}

	fn make_oriented(&mut self, source: i32, drain: i32) -> bool
	{
		if source < (f64::sqrt(self.aadMatrix.len() as f64)) as i32 &&
			drain < (f64::sqrt(self.aadMatrix.len() as f64)) as i32
		{
			for i in 0..(f64::sqrt(self.aadMatrix.len() as f64)) as usize
			{
				self.aadMatrix[i][source as usize] = 0;
				self.aadMatrix[drain as usize][i] = 0;
			}
			return false;
		}
		true
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
	graph.aadMatrix[0][1] = 20;
    graph.aadMatrix[1][0] = 20;
    graph.aadMatrix[1][3] = 16;
    graph.aadMatrix[3][1] = 16;
    graph.aadMatrix[1][5] = 3;
    graph.aadMatrix[5][1] = 3;
    graph.aadMatrix[2][4] = 10;
    graph.aadMatrix[4][2] = 10;
    graph.aadMatrix[4][5] = 14;
    graph.aadMatrix[5][4] = 14;
    graph.aadMatrix[2][1] = -4;
    graph.aadMatrix[1][2] = 4;
    graph.aadMatrix[4][3] = 1;
    graph.aadMatrix[3][4] = -1;

    graph.make_oriented(0, 5);
    graph.reset_visitance();

    let mut d = 999999;
    while d > 0
    {
    	d = graph.dfs_ford(0, 999999);
    	println!("{}", d);
    }

    
}