import React from 'react';
import { connect } from 'react-redux';
import { Button, FormGroup, Label, Input } from 'reactstrap';
import api from '../api';

function TaskForm(props) {

  function update(ev) {
    let tgt = $(ev.target);

    let data = {};
    data[tgt.attr('name')] = tgt.val();
    let action = {
      type: 'UPDATE_FORM',
      data: data,
    };
    console.log(action);
    props.dispatch(action);
  }

  function updateCompleted(ev) {
  	let tgt = $(ev.target);
    let data = {};
    if (tgt.val() === 'false') {
    	data[tgt.attr('name')] = true;
    } else {
    	data[tgt.attr('name')] = false;
    }
    props.dispatch({
      type: 'UPDATE_FORM',
      data: data,
    });
  }

  function submit(ev) {
    api.submit_task(props.form);
    console.log(props.form);
  }

  function clear(ev) {
    props.dispatch({
      type: 'CLEAR_FORM',
    });
  }

  let users = _.map(props.users, (uu) => <option key={uu.id} value={uu.id}>{uu.name}</option>);
  return <div style={{padding: "4ex"}}>
    <h2>New Task</h2>
    <FormGroup>
      <Label for="user_id">User</Label>
      <Input type="select" name="user_id" value={props.form.user_id} onChange={update}>
        { users }
      </Input>
    </FormGroup>
    <FormGroup>
      <Label for="title">Title</Label>
      <Input type="textarea" name="title" value={props.form.title} onChange={update} />
    </FormGroup>
    <FormGroup>
      <Label for="description">Description</Label>
      <Input type="textarea" name="description" value={props.form.description} onChange={update} />
    </FormGroup>
    <FormGroup>
      <Label for="completed">Completed</Label>
      <Input type="checkbox" name="completed" value={props.form.completed} onChange={updateCompleted} />
    </FormGroup>
    <FormGroup>
      <Label for="time">Time</Label>
      <Input type="number "step="15" 
						min="0"  name="time" value={props.form.time} onChange={update} />
    </FormGroup>
    <Button onClick={submit} color="primary">Make Task</Button> &nbsp;
    <Button onClick={clear}>Clear</Button>
  </div>;
}

function state2props(state) {
  return {
    form: state.form,
    users: state.users,
  };
}

export default connect(state2props)(TaskForm);