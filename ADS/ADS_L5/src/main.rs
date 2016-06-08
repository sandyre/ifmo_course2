extern crate rand;

use std::io::prelude::*;
use std::fs::File;

fn triad_to_int( string: &String ) 
	-> i8
{
	let mut result = 0i8;
	let mut str_chars = string.chars();

	match str_chars.next().unwrap()
	{
		'1' => result += 4,
		_ 	=> (),
	}

	match str_chars.next().unwrap()
	{
		'1' => result += 2,
		_	=> (),
	}

	match str_chars.next().unwrap()
	{
		'1' => result += 1,
		_	=> (),
	}

	result
}

fn integer_to_string( integer: u64 )
	-> String
{
	let mut result = String::new();
	let mut twos_power: u64 = 1 << 63;

	for i in 0..64
	{
		if (integer & twos_power) != 0
		{
			result.push('1');
		}
		else 
		{
			result.push('0');	
		}

		twos_power >>= 1;
	}

	result
}

fn split_string_to_triads( string: String )
	-> Vec<String>
{
	let mut tmp_str = String::new();
	let mut result_vector = vec![String::new();0];

	for i in string.chars().rev()
	{
		tmp_str.push(i);

		if tmp_str.len() == 3
		{
			tmp_str = tmp_str.chars().rev().collect();
			result_vector.push( tmp_str );
			tmp_str = String::new();
		}
	}

	match tmp_str.len()
	{
		0 => (),
		1 =>
		{
			let mut n_str = format!("00{}", tmp_str);
			result_vector.push( n_str );
		},
		2 =>
		{
			tmp_str = tmp_str.chars().rev().collect();
			let mut n_str = format!("0{}", tmp_str);
			result_vector.push( n_str );
		},
		_ => panic!("That should never happen."),
	}

	result_vector.reverse();
	result_vector
}

fn main()
{
	let mut file = File::open( "test_data.txt" ).unwrap();
	let mut file_data = String::new();
	file.read_to_string( &mut file_data ).unwrap();
	let mut vectar = split_string_to_triads( file_data );
	let mut triads_sum: u64 = 100;

	while triads_sum > 7
	{
		triads_sum = 0;
		for i in &vectar
		{
			triads_sum += triad_to_int( &i ) as u64;
		}

		println!("Triads sum: {}", triads_sum);

		vectar = split_string_to_triads( integer_to_string(triads_sum) );
	}

	match triads_sum
	{
		7 => println!("Hola! Its divisible by 7."),
		_ => println!("Its not divisible by 7."),
	}
}